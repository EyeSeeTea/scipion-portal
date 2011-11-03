package particlepicker.training.gui;

import ij.gui.ImageWindow;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.util.List;

import javax.swing.SwingUtilities;

import particlepicker.ParticlePickerCanvas;
import particlepicker.ParticlePickerJFrame;
import particlepicker.Tool;
import particlepicker.training.model.AutomaticParticle;
import particlepicker.training.model.FamilyState;
import particlepicker.training.model.MicrographFamilyData;
import particlepicker.training.model.TrainingMicrograph;
import particlepicker.training.model.TrainingParticle;
import particlepicker.training.model.TrainingPicker;

public class TrainingCanvas extends ParticlePickerCanvas
{

	private TrainingPickerJFrame frame;
	private TrainingMicrograph micrograph;
	private TrainingParticle active;
	private TrainingPicker ppicker;
	final static BasicStroke dashedst = new BasicStroke(1.0f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10.0f, new float[] { 10.0f }, 0.0f);
	final static BasicStroke continuousst = new BasicStroke();

	public TrainingCanvas(TrainingPickerJFrame frame)
	{
		super(frame.getMicrograph().getImagePlus());
		this.micrograph = frame.getMicrograph();
		this.frame = frame;
		addMouseWheelListener(this);
		this.ppicker = frame.getParticlePicker();
		if(!frame.getFamilyData().getParticles().isEmpty())
			active = frame.getFamilyData().getParticles().get(frame.getFamilyData().getParticles().size() - 1);
		else
			active = null;

	}

	public void updateMicrograph()
	{
		this.micrograph = frame.getMicrograph();
		ImageWindow iw = (ImageWindow) getParent();
		iw.setImage(micrograph.getImagePlus());
		iw.updateImage(micrograph.getImagePlus());
		iw.setTitle(micrograph.getName());
		imp = micrograph.getImagePlus();
		if(!frame.getFamilyData().getParticles().isEmpty())
			setActive(frame.getFamilyData().getParticles().get(frame.getFamilyData().getParticles().size() - 1));
		else
			active = null;
	}

	/**
	 * Adds particle or updates its position if onpick. If ondeletepick removes
	 * particle. Considers owner for selection to the first particle containing
	 * point. Sets dragged if onpick
	 */

	public void mousePressed(MouseEvent e)
	{
		super.mousePressed(e);
		if (frame.isPickingAvailable(e))
		{

			int x = super.offScreenX(e.getX());
			int y = super.offScreenY(e.getY());
			TrainingParticle p = micrograph.getParticle(x, y);
			if (p == null)
				p = micrograph.getAutomaticParticle(x, y, frame.getThreshold());
			if (p != null)
			{
				if (SwingUtilities.isLeftMouseButton(e) && e.isControlDown())
				{
					micrograph.removeParticle(p, ppicker);
					frame.updateMicrographsModel();
					active = frame.getFamilyData().getParticles().get(frame.getFamilyData().getParticles().size() - 1);
				}
				else if (SwingUtilities.isLeftMouseButton(e))
				{
					active = p;
				}
			}
			else if (SwingUtilities.isLeftMouseButton(e) && TrainingParticle.boxContainedOnImage(x, y, frame.getFamily().getSize(), imp))
			{
				p = new TrainingParticle(x, y, frame.getFamily(), micrograph);
				micrograph.addManualParticle(p);
				active = p;
				frame.updateMicrographsModel();
			}
			frame.setChanged(true);
			repaint();
		}
	}

	/**
	 * Updates particle position and repaints if onpick.
	 */
	@Override
	public void mouseDragged(MouseEvent e)
	{

		super.mouseDragged(e);
		int x = super.offScreenX(e.getX());
		int y = super.offScreenY(e.getY());

		if (frame.isPickingAvailable(e))
		{
			if (active == null)
				return;

			if (!TrainingParticle.boxContainedOnImage(x, y, active.getFamily().getSize(), imp))
				return;
			if (active instanceof AutomaticParticle)
			{
				micrograph.removeParticle(active, ppicker);
				active = new TrainingParticle(active.getX(), active.getY(), active.getFamily(), micrograph);
				micrograph.addManualParticle(active);
			}
			else
			{
				active.setPosition(x, y);
				if (frame.getParticlesJDialog() != null)
					active.getParticleCanvas(frame).repaint();
			}
			frame.setChanged(true);
			repaint();
		}
	}

	public void paint(Graphics g)
	{
		super.paint(g);
		Graphics2D g2 = (Graphics2D) g;
		if (frame.getFamily().getStep() == FamilyState.Manual)
			for (MicrographFamilyData mfdata : micrograph.getFamiliesData())
				drawFamily(g2, mfdata);
		else
			drawFamily(g2, micrograph.getFamilyData(frame.getFamily()));
		if (active != null)
		{
			g2.setColor(Color.red);
			drawShape(g2, active, true);
		}

	}

	private void drawFamily(Graphics2D g2, MicrographFamilyData mfdata)
	{
		List<TrainingParticle> particles;
		int index;
		if (!mfdata.isEmpty())
		{
			particles = mfdata.getManualParticles();
			g2.setColor(mfdata.getFamily().getColor());

			for (index = 0; index < particles.size(); index++)
				drawShape(g2, particles.get(index), index == particles.size() - 1);
			List<AutomaticParticle> autoparticles = mfdata.getAutomaticParticles();
			for (int i = 0; i < autoparticles.size(); i++)
				if (!autoparticles.get(i).isDeleted() && autoparticles.get(i).getCost() >= frame.getThreshold())
					drawShape(g2, autoparticles.get(i), false);
		}
	}

	@Override
	public void setActive(TrainingParticle p)
	{
		active = p;
		repaint();

	}

	@Override
	public ParticlePickerJFrame getFrame()
	{
		return frame;
	}

}
