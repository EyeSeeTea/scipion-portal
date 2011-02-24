/***************************************************************************
 * Authors:     Joaquin Oton (joton@cnb.csic.es)
 *
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

#include "image.h"

#include "image_generic.h"


ImageGeneric::ImageGeneric(DataType _datatype)
{
    init();
    setDatatype(_datatype);
}

ImageGeneric::~ImageGeneric()
{
    delete image;
    delete data;
}

void ImageGeneric::init()
{
    image = NULL;
    data = NULL;
    datatype = Unknown_Type;
}

void ImageGeneric::clear()
{
    if (image != NULL)
    {
        image->clear();
        delete image;
        init();
    }
}

void ImageGeneric::getImageType(const FileName &imgName, DataType &datatype)
{
    Image<char> Im;
    Im.read(imgName, HEADER);
    datatype = Im.dataType();
}

void ImageGeneric::getImageType(const FileName &imgName, DataType &datatype, bool &swap)
{
    Image<char> Im;
    Im.read(imgName, HEADER);
    datatype = Im.dataType();
    int iswap;
    Im.getSwap(iswap);
    swap = (swap > 0);
}

void ImageGeneric::setDatatype(DataType imgType)
{
    clear();
    datatype = imgType;
    switch (datatype)
    {
    case Float:
        {
            Image<float> *imT = new Image<float>;
            image = imT;
            data = new MultidimArrayGeneric((MultidimArrayBase*) &(imT->data), datatype);
        }
        break;
    case UInt:
        {
            Image<unsigned int> *imT = new Image<unsigned int>;
            image = imT;
            data = new MultidimArrayGeneric((MultidimArrayBase*) &(imT->data), datatype);
        }
        break;
    case Int:
        {
            Image<int> *imT = new Image<int>;
            image = imT;
            data = new MultidimArrayGeneric((MultidimArrayBase*) &(imT->data), datatype);
        }
        break;
    case UShort:
        {
            Image<unsigned short> *imT = new Image<unsigned short>;
            image = imT;
            data = new MultidimArrayGeneric((MultidimArrayBase*) &(imT->data), datatype);
        }
        break;
    case Short:
        {
            Image<short> *imT = new Image<short>;
            image = imT;
            data = new MultidimArrayGeneric((MultidimArrayBase*) &(imT->data), datatype);
        }
        break;
    case UChar:
        {
            Image<unsigned char> *imT = new Image<unsigned char>;
            image = imT;
            data = new MultidimArrayGeneric((MultidimArrayBase*) &(imT->data), datatype);
        }
        break;
    case SChar:
        {
            Image<char> *imT = new Image<char>;
            image = imT;
            data = new MultidimArrayGeneric((MultidimArrayBase*) &(imT->data), datatype);
        }
        break;
    case Unknown_Type:
        REPORT_ERROR(ERR_IMG_UNKNOWN,"");
        break;
    default:
        REPORT_ERROR(ERR_NOT_IMPLEMENTED, "Datatype not implemented.");
        break;
    }
}

int ImageGeneric::read(const FileName &name, DataMode datamode, size_t select_img,
                       bool mapData)
{
    bool swap;
    DataType datatype;
    getImageType(name, datatype, swap);
    setDatatype(datatype);
    image->read(name, datamode, select_img, mapData && swap);
}

int ImageGeneric::readApplyGeo(const FileName &name, const MDRow &row, bool only_apply_shifts, DataMode datamode, size_t select_img)
{
    DataType datatype;
    getImageType(name, datatype);
    setDatatype(datatype);
    image->readApplyGeo(name, row, only_apply_shifts, datamode, select_img);
}

int ImageGeneric::readApplyGeo(const FileName &name, const MetaData &md, size_t objId, bool only_apply_shifts, DataMode datamode,
                               size_t select_img)
{
    DataType datatype;
    getImageType(name, datatype);
    setDatatype(datatype);
    image->readApplyGeo(name, md, objId, only_apply_shifts, datamode, select_img);
}

/** Read an image from metadata, filename is taken from MDL_IMAGE */
int ImageGeneric::readApplyGeo(const MetaData &md, size_t objId, bool only_apply_shifts, DataMode datamode, size_t select_img)
{
    FileName name;
    md.getValue(MDL_IMAGE, name, md.firstObject());
    DataType datatype;
    getImageType(name, datatype);
    setDatatype(datatype);
    image->readApplyGeo(name, md, objId, only_apply_shifts, datamode, select_img);
}

void  ImageGeneric::mapFile2Write(int Xdim, int Ydim, int Zdim, int Ndim, FileName _filename,
                                  bool createTempFile)
{
    image->setDataMode(HEADER); // Use this to ask rw* which datatype to use
    image->mapFile2Write(Xdim,Ydim,Zdim,Ndim,_filename,createTempFile);

    DataType writeDT = image->dataType();
    if ( writeDT != datatype)
    {
        setDatatype(writeDT);
        image->mapFile2Write(Xdim,Ydim,Zdim,Ndim,_filename,createTempFile);
    }
}


void ImageGeneric::print() const
{
    std::cout << *image;
}
