package xmipp.viewer;


import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.Image;

import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JTable;
import javax.swing.border.Border;
import javax.swing.table.DefaultTableCellRenderer;

import xmipp.utils.ColorIcon;
import xmipp.utils.CompoundIcon;
import xmipp.utils.DEBUG;
import xmipp.utils.XmippResource;
import xmipp.viewer.models.ImageGallery;
import xmipp.viewer.windows.ClassesJDialog.ClassInfo;

/**
 * 
 * @author Juanjo Vega
 */
public class ImageItemRenderer extends DefaultTableCellRenderer {
	private static final long serialVersionUID = 1L;

	Border BORDER_SELECTED = new StrokeBorder(Color.RED, 3);
	Border BORDER_FOCUSED = BorderFactory.createLineBorder(Color.RED, 3);
	boolean hackBorders = true;

	public ImageItemRenderer() {
		super();
		setOpaque(true);
		setHorizontalAlignment(JLabel.CENTER);
		setHorizontalTextPosition(JLabel.CENTER);
		setVerticalTextPosition(JLabel.BOTTOM);
	}

	public ImageItemRenderer(boolean hackBorders) {
		this();
		this.hackBorders = false;
	}

	@Override
	public Component getTableCellRendererComponent(JTable table, Object object,
			boolean isSelected, boolean hasFocus, int row, int column) {
		ImageGallery.ImageItem item = (ImageGallery.ImageItem) object;
		// DEBUG.printMessage("*** 1. Rendering: " + item.getLabel());
		// Calls super class so foreground, background, borders and rest of
		// stuff is set.
		super.getTableCellRendererComponent(table, null, item != null
				&& item.isSelected(), item != null && hasFocus, row, column);

		if (item != null) {
			// DEBUG.printMessage("*** 2. Rendering: " + item.getLabel());
			// AbstractXmippTableModel tableModel = (AbstractXmippTableModel)
			// table.getModel();

			setPreferredSize(item.getCellDim());

			// Loads image...
			Image image = item.getImage();
			Icon icon;
			
			if (image != null)
				icon = new ImageIcon(image);
			else
				icon = XmippResource.MISSING_ICON;
			
			if (!item.isEnabled()){
				icon = new CompoundIcon(CompoundIcon.Axis.Z_AXIS, 0, 
						CompoundIcon.RIGHT, CompoundIcon.BOTTOM, icon,
						XmippResource.DELETE_ICON);
						//new ColoredRectangleIcon(Color.red, 16, 16));
			}

			if (item.isBusy()) {
				icon = new CompoundIcon(CompoundIcon.Axis.Z_AXIS, 0, 
						CompoundIcon.RIGHT, CompoundIcon.BOTTOM, icon,
						 XmippResource.LOCK_ICON);	
			}
			ClassInfo cli = item.getClassInfo();
			if (cli != null){
				icon = new CompoundIcon(CompoundIcon.Axis.Z_AXIS, 0, 
						CompoundIcon.RIGHT, CompoundIcon.BOTTOM, icon,
						cli.getIcon());
						
			}
			setIcon(icon);
			// Tooltip.
			setToolTipText(item.getLabel());

			// (Shows label only when required).
			if (item.getShowLabel()) {
				String label = cutString(item.getLabel(), table
						.getColumnModel().getColumn(column).getWidth());
				setText(label);
			} else {
				setText(null);
			}

			if (hackBorders) {
				// Hacking borders to enhance the default one.
				if (item.isSelected()) {
					setBorder(BORDER_SELECTED);
				}

				// if (hasFocus) {
				// setBorder(BORDER_FOCUSED);
				// }
			}
		} else {
			setIcon(null);
			setText(null);
			setToolTipText(null);
		}

		return this;
	}

	protected String cutString(String string, int columnWidth) {
		StringBuilder sb = new StringBuilder(string);
		String str = sb.toString();

		Font font = getFont();
		int w = getFontMetrics(font).stringWidth(str);

		int i = 0;
		while (w > columnWidth) {
			str = "..." + sb.substring(i++);
			w = getFontMetrics(font).stringWidth(str);
		}

		return str;
	}
}
