package xmipp.particlepicker.extract;


import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.event.MouseEvent;

import javax.swing.SwingUtilities;

import xmipp.jni.Particle;
import xmipp.particlepicker.Micrograph;
import xmipp.particlepicker.ParticlePickerCanvas;
import xmipp.particlepicker.ParticlePickerJFrame;
import xmipp.particlepicker.training.model.AutomaticParticle;
import xmipp.particlepicker.training.model.TrainingParticle;

public class ExtractCanvas extends ParticlePickerCanvas
{

	private ExtractPickerJFrame frame;
	private ExtractMicrograph micrograph;
	private ExtractParticle active;
	private ExtractParticlePicker picker;

	public ExtractCanvas(ExtractPickerJFrame frame)
	{
		super(frame.getMicrograph().getImagePlus(frame.getParticlePicker().getFilters()));
		this.frame = frame;
		this.picker = frame.getParticlePicker();
		this.micrograph = frame.getMicrograph();
		micrograph.runImageJFilters(frame.getParticlePicker().getFilters());
		active = getLastParticle();
	}

	@Override
	public void refreshActive(Particle p)
	{
		active = (ExtractParticle)p;
		repaint();
		
	}

	@Override
	public ExtractParticle getActive()
	{
		return active;
	}

	@Override
	public ParticlePickerJFrame getFrame()
	{
		return frame;
	}

	@Override
	public Micrograph getMicrograph()
	{
		return micrograph;
	}
	
	

	@Override
	protected void doCustomPaint(Graphics2D g2)
	{
		g2.setColor(frame.getColor());

		for (ExtractParticle p : micrograph.getParticles())
			if(p.isEnabled())
				drawShape(g2, p.getX(), p.getY(), frame.getParticlePicker().getSize(), false, continuousst);
			else
				drawShape(g2, p.getX(), p.getY(), frame.getParticlePicker().getSize(), false, dashedst);
		if (active != null)
		{
			g2.setColor(Color.red);
			Stroke stroke = active.isEnabled() ? activecst: activedst;
			drawShape(g2, active.getX(), active.getY(), frame.getParticlePicker().getSize(), true, stroke);
		}
	}

	@Override
	protected ExtractParticle getLastParticle()
	{
		if(micrograph.getParticles().isEmpty())
			return null;
		return micrograph.getParticles().get(micrograph.getParticles().size() - 1);
	}

	
	public void mousePressed(MouseEvent e)
	{
		super.mousePressed(e);
		int x = super.offScreenX(e.getX());
		int y = super.offScreenY(e.getY());
		
		if (frame.isPickingAvailable(e))
		{
			if(frame.isEraserMode())
			{
				micrograph.removeParticles(x, y, picker);
				active = getLastParticle();
				refresh();
				
				return;
			}
			ExtractParticle p =  micrograph.getParticle(x, y, picker.getSize());
			
				
			
			if (p != null)
			{
				if (SwingUtilities.isLeftMouseButton(e) && e.isShiftDown())
				{
					micrograph.removeParticle(p);
					active = getLastParticle();
				}
				else if (SwingUtilities.isLeftMouseButton(e))
					active = p;
			}
			
			refresh();
		}
	}
	
	@Override
	public void mouseDragged(MouseEvent e)
	{

		super.mouseDragged(e);
		int x = super.offScreenX(e.getX());
		int y = super.offScreenY(e.getY());
		if (frame.isPickingAvailable(e))
		{
			if(frame.isEraserMode())
			{
				micrograph.removeParticles(x, y, picker);
				active = getLastParticle();
				refresh();
				return;
			}
			if (active == null)
				return;

			if (!micrograph.fits(x, y, picker.getSize()))
				return;
			moveActiveParticle(x, y);
			active.setEnabled(true);//if it was disabled gets enabled
			frame.setChanged(true);
			repaint();
		}
	}

	@Override
	public void setMicrograph(Micrograph m)
	{
		micrograph = (ExtractMicrograph)m;
		
	}
	
}
