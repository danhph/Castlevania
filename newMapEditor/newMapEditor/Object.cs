
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
namespace newMapEditor
{
    class Object
    {
        Boolean _selected = false;
        public static int count = 0;
        int _id;
        String _name;
        int _type;
        int _X;
        int _Y;
        int _width;
        int _height;
        public Object(int id, String name, int type, int X, int Y, int Width, int Height)
        {
            _id = id;
            _name = name;
            _type = type;
            _X = X;
            _Y = Y;
            _width = Width;
            _height = Height;
        }
        public Object(int X, int Y, int Width, int Height)
        {
            _id = count++;
            _name = "object" + count.ToString();
            _X = X;
            _Y = Y;
            _width = Width;
            _height = Height;
        }

        [Browsable(false)]
        public Boolean Selected
        {
            get
            {
                return _selected;
            }
            set
            {
                _selected = value;
            }
        }
        public int ID
        {
            get
            {
                return _id;
            }
            set
            {
                _id = value;
            }
        }
        public String Name
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
            }
        }
        public int Type
        {
            get
            {
                return _type;
            }
            set
            {
                _type = value;
            }
        }
        public int X
        {
            get
            {
                return _X;
            }
            set
            {
                _X = value;
            }
        }
        public int Y
        {
            get
            {
                return _Y;
            }
            set
            {
                _Y = value;
            }
        }
        public int Width
        {
            get
            {
                return _width;
            }
            set
            {
                _width = value;
            }
        }
        public int Height
        {
            get
            {
                return _height;
            }
            set
            {
                _height = value;
            }
        }
        public void Draw(Graphics g,float scaleFactor)
        {
            g.FillRectangle(new SolidBrush(Color.FromArgb(128, 0, 0, 255)), new Rectangle((int)(_X * scaleFactor), (int)(_Y * scaleFactor), (int)(_width * scaleFactor) + 1, (int)(_height * scaleFactor) + 1));
            g.DrawString(_name, new Font(FontFamily.GenericSansSerif,8*scaleFactor, FontStyle.Regular),Brushes.Black, (int)(_X * scaleFactor), (int)(_Y * scaleFactor));
            if (_selected==true)
            {
                g.DrawRectangle(new Pen(Brushes.Red, 2), new Rectangle((int)(_X*scaleFactor), (int)(_Y*scaleFactor),(int)(_width*scaleFactor)+1, (int)(_height*scaleFactor)+1));
            }
        }
    }
}
