using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace ThermoMap_GUI
{
    
    public partial class Form1 : Form
    {
        private TcpListener listener;
        public Form1()
        {
            InitializeComponent();
            StartListening();
        }
        private void StartListening()
        {
            try
            {
                listener = new TcpListener(IPAddress.Any, 8080);
                listener.Server.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
                listener.Start();
                listener.BeginAcceptTcpClient(new AsyncCallback(HandleIncomingConnection), listener);
            }
            catch (Exception ex)
            {
                label2.Text = ("Error: " + ex.Message);
            }
        }

        private void HandleIncomingConnection(IAsyncResult result)
        {
            TcpListener listener = (TcpListener)result.AsyncState;
            TcpClient client = null;

            try
            {
                client = listener.EndAcceptTcpClient(result);
                NetworkStream stream = client.GetStream();
                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string requestData = Encoding.ASCII.GetString(buffer, 0, bytesRead);

                // Do something with the received data
                SetLabelText(requestData);

                // Here you can process the received data and update your GUI accordingly
            }
            catch (Exception ex)
            {
                SetLabelText("Error: " + ex.Message);
            }
            finally
            {
                client?.Close();
                listener.BeginAcceptTcpClient(new AsyncCallback(HandleIncomingConnection), listener);
            }
        }

        private void SetLabelText(string text)
        {
            if (label2.InvokeRequired)
            {
                label2.Invoke(new Action(() => label2.Text = text));
            }
            else
            {
                label2.Text = text;
            }
        }

        // Don't forget to close the listener when your application exits
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            if (listener != null)
            {
                listener.Stop();
            }
        }

    }
}
