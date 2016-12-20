using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace newMapEditor
{
    class Background
    {
        TileSet _tileset;
        int[][] _background;
        int _width;
        int _height;
        public Background(TileSet tileset, int width, int height,int[][] background)
        {
            _width = width;
            _height = height;
            _tileset = tileset;
            _background = background;
        }
        public Background(TileSet tileset, int width, int height)
        {
            _width = width;
            _height = height;
            _tileset = tileset;
            _background = new int[_height][];
            for (int i = 0; i < _height; i++)
                _background[i] = new int[_width];
            resetBackground();
        }
        public void resetBackground()
        {
            for (int i = 0; i < _height; i++)
                for (int j = 0; j < _width; j++)
                {
                    _background[i][j] = -1;
                }
        }
        public int this[int row,int column]{
            get{
                return _background[row][column];
            }
            set
            {

                _background[row][column] = value;
            }

        }
        public void Draw(Graphics g,float scaleFactor)
        {
            for (int i=0;i<_height;i++)
                for (int j=0;j<_width;j++)
                {
                    if (_background[i][j]>-1)
                        _tileset[_background[i][j]].Draw(g,j,i,scaleFactor);
                }
        }
        public int MapWidth
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
        public int MapHeight
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
        public TileSet TileSet
        {
            get
            {
                return _tileset;
            }
            set
            {
                _tileset = value;
            }
        }
    }
}
