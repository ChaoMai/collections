using System;
using System.Windows.Forms;
using System.Net.NetworkInformation;

namespace NetSpeed
{
    class Program
    {
        private NotifyIcon trayIcon;
        private ContextMenuStrip trayIconContextMenu;
        private ToolStripMenuItem closeMenuItem;

        static void Main(string[] args)
        {
            Program prog = new Program();
            prog.Initialize();
            Application.Run();
        }

        void Initialize()
        {
            trayIcon = new NotifyIcon();
            trayIcon.BalloonTipIcon = ToolTipIcon.Info;
            trayIcon.BalloonTipTitle = "NetSpeed";
            trayIcon.Icon = Properties.Resources.TrayIcon;
            trayIcon.Text = "NetSpeed";
            trayIcon.Click += TrayIcon_Click;
            trayIcon.Visible = true;

            trayIconContextMenu = new ContextMenuStrip();
            closeMenuItem = new ToolStripMenuItem();

            trayIconContextMenu.Items.AddRange(new ToolStripItem[] { closeMenuItem });
            trayIconContextMenu.Name = "Context Menu";
            trayIconContextMenu.Size = new System.Drawing.Size(150, 50);

            closeMenuItem.Name = "Menu";
            closeMenuItem.Size = new System.Drawing.Size(150, 20);
            closeMenuItem.Text = "Close";
            closeMenuItem.Click += CloseMenuItem_Click;

            trayIcon.ContextMenuStrip = trayIconContextMenu;
            Application.ApplicationExit += Application_ApplicationExit;
        }

        private void TrayIcon_Click(object sender, EventArgs e)
        {
            var me = (MouseEventArgs)e;

            if (me.Button == MouseButtons.Left)
            {
                GetNetWorkSpeed();
                trayIcon.BalloonTipText = "tip";
                trayIcon.ShowBalloonTip(500);
            }
        }

        private void Application_ApplicationExit(object sender, EventArgs e)
        {
            trayIcon.Visible = false;
        }

        private void CloseMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private Tuple<string,string> GetNetWorkSpeed()
        {
            var adapters = NetworkInterface.GetAllNetworkInterfaces();
            foreach(var adapter in adapters)
            {
                IPInterfaceProperties properties = adapter.GetIPProperties();
                IPv4InterfaceStatistics stats = adapter.GetIPv4Statistics();
                Console.WriteLine("speed {0}", adapter.Speed);
                Console.WriteLine("length {0}", stats.OutputQueueLength);
            }

            return null;
        }
    }
}