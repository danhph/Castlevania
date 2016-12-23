using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace newMapEditor
{
    public class TileSet
    {
        Dictionary<int, Tile> dictTiles;
        private String _name;
        private Image _image;
        private int _tileWidth;
        private int _tileHeight;
        private int _rows;
        private int _columns;
        private int _count;
        public int Count
        {
            get
            {
                return _count;
            }
            set
            {
                _count = value;
            }
        }
        public int Rows
        {
            get
            {
                return _rows;
            }
            set
            {
                _rows = value;
            }
        }
        public int Columns
        {
            get
            {
                return _columns;
            }
            set
            {
                _columns = value;
            }
        }
        public int TileWidth
        {
            get
            {
                return _tileWidth;
            }
            set
            {
                _tileWidth = value;
            }
        }
        public int TileHeight
        {
            get
            {
                return _tileHeight;
            }
            set
            {
                _tileHeight = value;
            }
        }
        public Image Image
        {
            get
            {
                return _image;
            }
            set
            {
                _image = value;
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
        public TileSet(String name, String filePath, int tileWidth, int tileHeight)
        {
            _image = new Bitmap(filePath);
            _name = name;
            _tileWidth = tileWidth;
            _tileHeight = tileHeight;
            _rows = _image.Width / _tileHeight;
            _columns = _image.Height / _tileWidth;
            _count = _rows * _columns;
            dictTiles = new Dictionary<int, Tile>();
            for (int i=0;i<_count;i++)
            {
                try
                {
                    Rectangle r = new Rectangle((i % _columns) * _tileWidth, (i / _columns) * _tileHeight, _tileWidth, _tileHeight);
                    dictTiles.Add(i, new Tile(((Bitmap)_image).Clone(r, Image.PixelFormat), _tileWidth, _tileHeight));
                }
                catch
                {
                    MessageBox.Show("Please choose right tiled picture");
                    return;
                }
            }
        }
        public void Draw(Graphics g,int id, int X, int Y,float scaleFactor)
        {
            dictTiles[id].Draw(g, X, Y,scaleFactor);
        }
        public Tile this[int key]
        {
            get
            {
                return dictTiles[key];
            }
        }


    }
}
