using System;
using System.Drawing;
using System.Windows.Forms;

public class Form1 : Form
{
    public static void Main()
    {
        Application.Run(new Form1());
    }
    public Form1()
    {
        Icon icon = new Icon("sample.ico");
        Text = "FirstCSharpWindow";
        Width = 800;
        Height = 600;
        BackColor = Color.Chartreuse;
        ResizeRedraw = true;
        this.KeyDown += new KeyEventHandler(KeyDownProc);
        this.MouseDown += new MouseEventHandler(MouseDownProc);
    }

    protected override void OnPaint(PaintEventArgs  paintEventArgs)
    {
        Graphics grphx = paintEventArgs.Graphics;
        StringFormat sfmt = new StringFormat();
        sfmt.Alignment = StringAlignment.Center;
        Font font = new Font(FontFamily.GenericSansSerif,48.0F, FontStyle.Bold);
        grphx.DrawString("Hello C#", font, new SolidBrush(System.Drawing.Color.Beige),ClientRectangle,sfmt   );
    }

    void KeyDownProc(Object sender, KeyEventArgs kArgs)
    {
        MessageBox.Show("'" + kArgs.KeyCode +  "' key is pressed");
    }
    void MouseDownProc(Object sender, MouseEventArgs mArgs)
    {
        MessageBox.Show(mArgs.Button + "key is pressed");
    }
}

