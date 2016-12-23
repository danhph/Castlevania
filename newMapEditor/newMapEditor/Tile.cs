
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
namespace newMapEditor
{
    public class Tile
    {
        private Image _image;
        private int _width;
        private int _height;
        public Tile(Bitmap pic, int width,int height)
        {
            _image = pic;
            _width = width;
            _height = height;
        }
        public Tile()
        {
        }
        public void Draw(Graphics g, int X, int Y,float scaleFactor)
        {
            g.DrawImage(_image,new Rectangle((int)(X*_width*scaleFactor),(int)(Y*_height*scaleFactor),(int)(_width*scaleFactor)+1,(int)(_height*scaleFactor)+1),new Rectangle(0,0,_width,_height),GraphicsUnit.Pixel);
        }
        public Image Image
        {
            get
            {
                return _image;
            }
        }
    }
}
