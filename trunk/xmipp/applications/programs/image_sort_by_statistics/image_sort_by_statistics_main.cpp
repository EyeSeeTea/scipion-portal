/***************************************************************************
 *
 * Authors: Carlos Oscar Sorzano (coss@cnb.csic.es)
 *          Sjors Scheres (scheres@cnb.csic.es)
 *
 * Unidad de  Bioinformatica of Centro Nacional de Biotecnologia , CSIC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307  USA
 *
 *  All comments concerning this program package may be sent to the
 *  e-mail address 'xmipp@cnb.csic.es'
 ***************************************************************************/

#include <data/basic_pca.h>
#include <data/histogram.h>
#include <data/image.h>
#include <data/fftw.h>
#include <data/args.h>
#include <data/metadata.h>
#include <data/metadata_extension.h>
#include <data/program.h>

class ProgSortByStatistics: public XmippProgram
{
public:
    FileName fn, fn_out, fn_train;
    bool multivariate;

public:
    double cutoff;
    MultidimArray<double> vavg, vstddev, Zscore, ZscoreMultivariate;
    PCAMahalanobisAnalyzer pcaAnalyzer;
    MetaData SF, SFtrain;

public:
    ProgSortByStatistics()
    {}

    void readParams()
    {
        fn = getParam("-i");
        SF.read(fn);
        fn_out = getParam("-o");
        multivariate = checkParam("--multivariate");
        fn_train = getParam("--train");
        if (fn_train != "")
            SFtrain.read(fn_train);
        cutoff = getDoubleParam("--zcut");
    }

    void defineParams()
    {
        addUsageLine("Sorts the input images for identifying junk particles");
        addUsageLine("+The program associates to each image a vector composed by");
        addUsageLine("+the histogram of the image (this accounts for factors such as");
        addUsageLine("+min, max, avg, and standard deviation, plus a more complete");
        addUsageLine("+description of the image gray levels) and the radial profile of");
        addUsageLine("+the image squared.");
        addUsageLine("+");
        addUsageLine("+These vectors are then scored according to a Gaussian distribution");
        addUsageLine("+that can be chosen to be univariate or multivariate. The multivariate");
        addUsageLine("+gaussian is more powerful in the sense that it can capture relationships");
        addUsageLine("+among variables.");
        addUsageLine("+");
        addUsageLine("+If you choose a threshold, you must take into account that it is a zscore.");
        addUsageLine("+For univariate and mulivariate Gaussian distributions, 99% of the individuals");
        addUsageLine("+have a Z-score below 3");
        addParamsLine(" -i <selfile>            : Selfile with input images");
        addParamsLine(" [-o <rootname=\"sort_junk\">] : Output rootname");
        addParamsLine("                               : rootname.sel contains the list of sorted images with their Z-score");
        addParamsLine("                               : rootname_vectors.xmd (if verbose>=2) contains the vectors associated to each image");
        addParamsLine(" [--train <selfile=\"\">]: Train on selfile with good particles");
        addParamsLine(" [--zcut <float=-1>]     : Cut-off for Z-scores (negative for no cut-off) ");
        addParamsLine("                         : Images whose Z-score is larger than the cutoff are disabled");
        addParamsLine(" [--multivariate]        : Identify also multivariate outliers");
    }

    void process_selfile(MetaData &SF, bool do_prepare, bool multivariate, bool quiet)
    {
        Image<double> img;
        MultidimArray<double> img2;
        MultidimArray<int> radial_count;
        MultidimArray<double> radial_avg;
        Matrix1D<int> center(2);
        center.initZeros();

        if (!quiet)
        {
            if (do_prepare)
                std::cerr << " Processing training set ..." << std::endl;
            else
                std::cerr << " Sorting particle set ..." << std::endl;
        }

        int nr_imgs = SF.size();
        if (!quiet)
            init_progress_bar(nr_imgs);
        int c = XMIPP_MAX(1, nr_imgs / 60);
        int imgno = 0, imgnoPCA=0;
        MultidimArray<float> v;
        MultidimArray<int> distance;
        int dim;
        if (do_prepare)
        {
            Zscore.initZeros(SF.size());
            ZscoreMultivariate=Zscore;
        }
        bool thereIsEnable=SF.containsLabel(MDL_ENABLED);
        bool first=true;
        FOR_ALL_OBJECTS_IN_METADATA(SF)
        {
            if (do_prepare)
            {
                if (thereIsEnable)
                {
                    int enabled;
                    SF.getValue(MDL_ENABLED,enabled,__iter.objId);
                    if (enabled==-1)
                        continue;
                }
                img.readApplyGeo(SF,__iter.objId);
                img().setXmippOrigin();
                img().statisticsAdjust(0,1);

                // Overall statistics
                Histogram1D hist;
                compute_hist(img(),hist,-4,4,31);

                // Radial profile
                img2.resizeNoCopy(img());
                FOR_ALL_ELEMENTS_IN_ARRAY2D(img2)
                {
                    double val=IMGPIXEL(img,i,j);
                    A2D_ELEM(img2,i,j)=val*val;
                }
                if (first)
                {
                    radialAveragePrecomputeDistance(img2, center, distance, dim);
                    first=false;
                }
                fastRadialAverage(img2, distance, dim, radial_avg, radial_count);

                // Build vector
                v.initZeros(XSIZE(hist)+XSIZE(img2)/2);
                int idx=0;
                FOR_ALL_DIRECT_ELEMENTS_IN_ARRAY1D(hist)
                v(idx++)=(float)DIRECT_A1D_ELEM(hist,i);
                for (int i=0; i<XSIZE(img2)/2; i++)
                    v(idx++)=(float)DIRECT_A1D_ELEM(radial_avg,i);
                pcaAnalyzer.addVector(v);
            }
            else
            {
                if (thereIsEnable)
                {
                    int enabled;
                    SF.getValue(MDL_ENABLED,enabled,__iter.objId);
                    if (enabled==-1)
                    {
                        Zscore(imgno)=1000;
                        if (multivariate)
                            ZscoreMultivariate(imgno)=1000;
                        imgno++;
                        continue;
                    }
                }
                v=pcaAnalyzer.v[imgnoPCA];
                FOR_ALL_DIRECT_ELEMENTS_IN_ARRAY1D(v)
                {
                    if (DIRECT_A1D_ELEM(vstddev,i)>0)
                    {
                        DIRECT_A1D_ELEM(v,i)=(DIRECT_A1D_ELEM(v,i)-DIRECT_A1D_ELEM(vavg,i))/
                                             DIRECT_A1D_ELEM(vstddev,i);
                        DIRECT_A1D_ELEM(v,i)=ABS(DIRECT_A1D_ELEM(v,i));
                    }
                    else
                        DIRECT_A1D_ELEM(v,i)=0;
                }
                Zscore(imgno)=v.computeAvg();
                if (multivariate)
                    ZscoreMultivariate(imgno)=pcaAnalyzer.getZscore(imgno);
            }

            if (imgno % c == 0 && !quiet)
                progress_bar(imgno);
            imgno++;
            imgnoPCA++;
        }
        if (!quiet)
            progress_bar(nr_imgs);

        if (do_prepare)
        {
            pcaAnalyzer.computeStatistics(vavg,vstddev);
            if (multivariate)
                pcaAnalyzer.evaluateZScore(2,20);
        }
    }

    void run()
    {
        // Process input selfile ..............................................
        if (fn_train != "")
            process_selfile(SFtrain, true, multivariate, verbose==0);
        else
            process_selfile(SF, true, multivariate, verbose==0);
        process_selfile(SF, false, multivariate, verbose==0);

        // Produce output .....................................................
        MetaData SFout;
        std::ofstream fh_zind;
        if (verbose==2)
            fh_zind.open((fn_out + "_vectors.xmd").c_str(), std::ios::out);
        MultidimArray<double> finalZscore=Zscore;
        double L=1;
        if (multivariate)
        {
            finalZscore*=ZscoreMultivariate;
            L++;
        }

        FOR_ALL_DIRECT_ELEMENTS_IN_ARRAY1D(finalZscore)
        DIRECT_A1D_ELEM(finalZscore,i)=pow(DIRECT_A1D_ELEM(finalZscore,i),1.0/L);

        MultidimArray<int> sorted;
        finalZscore.indexSort(sorted);
        int nr_imgs = SF.size();
        bool thereIsEnable=SF.containsLabel(MDL_ENABLED);
        for (int imgno = 0; imgno < nr_imgs; imgno++)
        {
            int isort = sorted(imgno) - 1;
            FileName fnImg;
            SF.getValue(MDL_IMAGE,fnImg,isort+1);
            if (thereIsEnable)
            {
                int enabled;
                SF.getValue(MDL_ENABLED,enabled,isort+1);
                if (enabled==-1)
                    continue;
            }
            size_t objId=SFout.addObject();
            SFout.setValue(MDL_IMAGE,fnImg,objId);
            if (finalZscore(isort)>cutoff && cutoff>0)
            	SFout.setValue(MDL_ENABLED,-1,objId);
            else
            	SFout.setValue(MDL_ENABLED,1,objId);
            SFout.setValue(MDL_ZSCORE,finalZscore(isort),objId);
            if (verbose==2)
            {
                fh_zind << fnImg << " : ";
                FOR_ALL_ELEMENTS_IN_ARRAY1D(pcaAnalyzer.v[isort])
                fh_zind << pcaAnalyzer.v[isort](i) << "\n";
            }
        }
        if (verbose==2)
            fh_zind.close();
        SFout.write(fn_out + ".sel");
    }
};

/**************************************************************************
        Main
/**************************************************************************/
int main(int argc, char **argv)
{
    ProgSortByStatistics prm;
    prm.read(argc,argv);
    return prm.tryRun();
}
