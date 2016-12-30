using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace newMapEditor
{
    class Objects
    {
        Boolean _selected = false;
        public static int count = 0;
        Dictionary<String, String> _properties;
        public Objects(int id, String name, int type, float X, float Y, float Width, float Height)
        {
            _properties = new Dictionary<String, String>();
            _properties["id"] = id.ToString();
            _properties["name"] = name;
            _properties["type"] = type.ToString();
            _properties["x"] = X.ToString();
            _properties["y"] = Y.ToString();
            _properties["width"] = Width.ToString();
            _properties["height"] = Height.ToString();
        }
        public Objects(int X, int Y, int Width, int Height)
        {
            _properties = new Dictionary<String, String>();
            _properties["id"] = (count++).ToString();
            _properties["name"] = "object" + count.ToString();
            _properties["x"] = X.ToString();
            _properties["y"] = Y.ToString();
            _properties["width"] = Width.ToString();
            _properties["height"] = Height.ToString();
        }
        public Dictionary<String, String> Property
        {
            get
            {
                return _properties;
            }
        }
        public String this[String key]
        {
            get
            {
                return _properties[key];
            }
            set
            {

                _properties[key] = value;
            }

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
        
        public void Draw(Graphics g, float scaleFactor)
        {
            g.FillRectangle(new SolidBrush(Color.FromArgb(128, 0, 0, 255)), new Rectangle((int)(float.Parse(_properties["x"]) * scaleFactor), (int)(float.Parse(_properties["y"]) * scaleFactor), (int)(float.Parse(_properties["width"]) * scaleFactor) + 1, (int)(float.Parse(_properties["height"]) * scaleFactor) + 1));
            g.DrawString(_properties["name"], new Font(FontFamily.GenericSansSerif, 8, FontStyle.Regular), Brushes.White, (int)(float.Parse(_properties["x"]) * scaleFactor), (int)(float.Parse(_properties["y"]) * scaleFactor));
            if (_selected == true)
            {
                g.DrawRectangle(new Pen(Brushes.Red, 2), new Rectangle((int)(float.Parse(_properties["x"]) * scaleFactor), (int)(float.Parse(_properties["y"]) * scaleFactor), (int)(float.Parse(_properties["width"]) * scaleFactor) + 1, (int)(float.Parse(_properties["height"]) * scaleFactor) + 1));
            }
        }
    }
}
