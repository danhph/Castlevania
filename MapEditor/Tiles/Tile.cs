using System.Drawing;

namespace MapEditor.Tiles
{
    public class Tile
    {
        public Tile(Image image, Rectangle srcRect, int id)
        {
            Id = id;
            SrcRect = srcRect;
            Image = ((Bitmap) image).Clone(SrcRect, image.PixelFormat);
        }

        public Rectangle SrcRect { get; }

        public int Id { get; }

        public Bitmap Image { get; }

        public void Draw(Graphics graphics, Point position, Size size)
        {
            graphics.DrawImage(Image, new Rectangle(position, size), SrcRect, GraphicsUnit.Pixel);
        }
    }
}