package xmipp.particlepicker;

import ij.gui.ImageCanvas;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Label;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

import xmipp.particlepicker.tiltpair.gui.TiltPairPickerJFrame;
import xmipp.particlepicker.tiltpair.gui.UntiltedMicrographCanvas;
import xmipp.particlepicker.tiltpair.model.TiltedMicrograph;
import xmipp.particlepicker.tiltpair.model.TiltedParticle;
import xmipp.particlepicker.tiltpair.model.UntiltedMicrograph;
import xmipp.particlepicker.tiltpair.model.UntiltedParticle;
import xmipp.particlepicker.training.gui.TrainingPickerJFrame;
import xmipp.particlepicker.training.model.TrainingMicrograph;
import xmipp.particlepicker.training.model.TrainingParticle;

public class ParticleCanvas extends ImageCanvas implements MouseMotionListener, MouseListener
{

	private TrainingParticle particle;
	private int size;
	private int lastx, lasty;
	private boolean dragged;
	private ParticlePickerJFrame frame;
	private ParticlePickerCanvas canvas;
	private int side;

	public ParticleCanvas(TrainingParticle particle, ParticlePickerJFrame frame)
	{
		super(particle.getMicrograph().getImagePlus());
		this.particle = particle;
		this.frame = frame;
		this.canvas = (particle instanceof TiltedParticle) ? ((TiltPairPickerJFrame) frame).getTiltedCanvas() : frame.getCanvas();

		this.size = (int) (frame.getFamily().getSize());
		side = frame.getSide(size);
		setMagnification((float) side / size);
		setDrawingSize(side, side);
		addMouseMotionListener(this);
		addMouseListener(this);
	}

	public void paint(Graphics g)
	{
		
		Rectangle source = new Rectangle(particle.getX0(), particle.getY0(), size, size);
		setSourceRect(source);
		super.paint(g);
		g.setColor(Color.white);
		g.drawRect(0, 0, side - 1, side - 1);
	}

	@Override
	public void mouseDragged(MouseEvent e)
	{
		if (dragged)
		{
			int movex = lastx - e.getX();
			int movey = lasty - e.getY();
			int x = particle.getX() + movex;
			int y = particle.getY() + movey;
			try
			{
				particle.setPosition(x, y);
				repaint();
				canvas.repaint();
				frame.setChanged(true);
			}
			catch (Exception ex)
			{
				canvas.repaint();
				repaint();
				JOptionPane.showMessageDialog(this, ex.getMessage());
				
			}
		}
		lastx = e.getX();
		lasty = e.getY();
	}

	@Override
	public void mousePressed(MouseEvent e)
	{
		if (frame.isPickingAvailable(e))
		{
			dragged = true;
			lastx = e.getX();
			lasty = e.getY();

			if (SwingUtilities.isLeftMouseButton(e) && e.isShiftDown())
			{
				if (frame instanceof TrainingPickerJFrame)
					((TrainingMicrograph) frame.getMicrograph()).removeParticle(particle, ((TrainingPickerJFrame) frame).getParticlePicker());
				else if (frame instanceof TiltPairPickerJFrame)
				{
					if (frame.getMicrograph() instanceof UntiltedMicrograph)
						((UntiltedMicrograph) frame.getMicrograph()).removeParticle((UntiltedParticle) particle);
					else if (frame.getMicrograph() instanceof TiltedMicrograph)
						((TiltedMicrograph) frame.getMicrograph()).removeParticle((TiltedParticle) particle);
				}
				canvas.repaint();
				frame.updateMicrographsModel();
				frame.loadParticles();
			}
			else
			{
				canvas.moveTo(particle);
				canvas.setActive(particle);
			}
		}

	}

	@Override
	public void mouseReleased(MouseEvent e)
	{
		dragged = false;

	}

}
