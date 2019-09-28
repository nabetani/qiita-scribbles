using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;

[DataContract]
public class Hoge
{
  [DataMember]
  public float foo { get; set; }
  [DataMember]
  public double bar { get; set; }
}

internal class JsonSerializer
{
  public static DataContractJsonSerializer Serializer<t>()
  {
    System.Type type = typeof(t);
    return new DataContractJsonSerializer(type);
  }
}

partial class Program
{
  static void Main(string[] args)
  {
    var t = new Hoge();
    t.foo = 0xa0000000L;
    t.bar = 0xa0000000L;
    using (var fs = System.Console.OpenStandardOutput())
    {
      JsonSerializer.Serializer<Hoge>().WriteObject(fs, t);
    }
  }
}

