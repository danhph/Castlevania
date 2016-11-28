using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Xml;

namespace MapEditor.Tiles
{
    internal class GameObject
    {
        public int Id { get; set; }

        public Rectangle ActiveBound { get; set; }

        public Rectangle InitBound { get; set; }

        public Dictionary<string, string> Parameters { get; set; }

        public static void Save(XmlTextWriter writter, List<GameObject> listObject, string path)
        {
            writter.WriteStartElement("Objects");
            {
                foreach (var gameObject in listObject)
                {
                    writter.WriteStartElement("Object");
                    {
                        writter.WriteAttributeString("Id", gameObject.Id.ToString());
                        writter.WriteAttributeString("X", gameObject.InitBound.X.ToString());
                        writter.WriteAttributeString("Y", gameObject.InitBound.Y.ToString());
                        writter.WriteAttributeString("Width", gameObject.InitBound.Width.ToString());
                        writter.WriteAttributeString("Height", gameObject.InitBound.Height.ToString());
                        writter.WriteStartElement("ActiveBound");
                        {
                            writter.WriteAttributeString("X", gameObject.ActiveBound.X.ToString());
                            writter.WriteAttributeString("Y", gameObject.ActiveBound.Y.ToString());
                            writter.WriteAttributeString("Width", gameObject.ActiveBound.Width.ToString());
                            writter.WriteAttributeString("Height", gameObject.ActiveBound.Height.ToString());
                        }
                        writter.WriteEndElement();
                        if (gameObject.Parameters.Any())
                        {
                            writter.WriteStartElement("Params");
                            {
                                foreach (KeyValuePair<string, string> elem in gameObject.Parameters.ToList())
                                {
                                    writter.WriteStartElement("Elem");
                                    writter.WriteAttributeString("Key", elem.Key);
                                    writter.WriteAttributeString("Value", elem.Value);
                                    writter.WriteEndElement();
                                }
                            }
                            writter.WriteEndElement();
                        }
                    }
                    writter.WriteEndElement();
                }
            }
            writter.WriteEndElement();
        }
    }
}