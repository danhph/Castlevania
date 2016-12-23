using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
namespace newMapEditor
{
    public partial class CreateTileSet : Form
    {
        Boolean Cancel = false;
        Bitmap buffer;
        Image image;
        Graphics gPicMain;
        Boolean OK = false;
        private TileSet tileset;
        private String filePath=null;
        private void Draw(int width, int height)
        {
                
                buffer = new Bitmap(image.Width, image.Height);
                gPicMain = Graphics.FromImage(buffer);
                
                //picMain.Image = image;

                gPicMain.DrawImage((Bitmap)image, new Rectangle(0,0,image.Width,image.Height));
                for (int i=0;i<width;i++)
                {
                    gPicMain.DrawLine(new Pen(Color.Blue, 1), new Point(i*(int)numWidth.Value, 0), new Point(i*(int)numWidth.Value, height*(int)numHeight.Value));
                }
                for (int i = 0; i < height; i++)
                {
                    gPicMain.DrawLine(new Pen(Color.Blue, 1), new Point(0, i*(int)numHeight.Value), new Point(width*(int)numWidth.Value, i * (int)numHeight.Value));
                }
            float scaleFactor = Math.Max((float)panel1.Width / image.Width, (float)panel1.Height / image.Height);
            if (scaleFactor>1)
            {

                picMain.Width = (int)(image.Width * scaleFactor);
                picMain.Height = (int)(image.Height * scaleFactor);
                Bitmap scaleBuffer = new Bitmap(buffer, new Size((int)(image.Width*scaleFactor),(int) (image.Height*scaleFactor)));
                //gPicMain.DrawImage(buffer, new Rectangle(0, 0, panel1.Width, panel1.Height), new Rectangle(0, 0, image.Width, image.Height), GraphicsUnit.Pixel);
                picMain.Image = scaleBuffer;
            }
            else
            {
                picMain.Width = image.Width;
                picMain.Height = image.Height;
                picMain.Image = buffer;
            }

            
        }
        public CreateTileSet()
        {
            InitializeComponent();
        }

        private void btnBrowser_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Image files (*.jpg, *.jpeg, *.jpe, *.jfif, *.png) | *.jpg; *.jpeg; *.jpe; *.jfif; *.png";
            openFileDialog1.Title = "Select a Tile";
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                filePath = openFileDialog1.FileName.ToString();
                image = new Bitmap(filePath);
                txtSource.Text = openFileDialog1.FileName.ToString();
                txtName.Text = openFileDialog1.SafeFileName.ToString();
                Draw(image.Width/(int)numWidth.Value,image.Height/(int)numHeight.Value);

            }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (filePath == null)
            {
                MessageBox.Show("You must choose tile picture");
            }
            else
            if (txtName.Text.Trim()==""||txtName.Text == null)
            {
                MessageBox.Show("You must name your file");
            }
            else
            if (numHeight.Value <= 0 || numWidth.Value <= 0)
                MessageBox.Show("Tile Width and Tile Height must be over 0");
            else
            {
                tileset = new TileSet(txtName.Text, filePath, (int)numWidth.Value, (int)numHeight.Value);
            }
            OK = true;
            this.Close();
        }

        private void num_ValueChanged(object sender, EventArgs e)
        {
            if (filePath != null)
            {
                Draw(image.Width / (int)numWidth.Value, image.Height / (int)numHeight.Value);
            }
        }
        public TileSet TileSet {
            get{
                return tileset;
            }
         }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Cancel = true;
            OK = false;
            this.Close();
        }
        public Boolean isOK {
        get {
                return OK;
            }
        }
        public Boolean isCancel
        {
            get
            {
                return Cancel;
            }
        }

        private void panel1_SizeChanged(object sender, EventArgs e)
        {
            if (filePath != null)
            {
                Draw(image.Width / (int)numWidth.Value, image.Height / (int)numHeight.Value);
            }
        }

        private void CreateTileSet_Load(object sender, EventArgs e)
        {
            
        }

        private void CreateTileSet_FormClosed(object sender, FormClosedEventArgs e)
        {
            Cancel = true;
        }
    }
}
