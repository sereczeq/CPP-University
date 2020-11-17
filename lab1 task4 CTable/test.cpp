public partial class ScreensaverForm : Form
{
    // variables to store cursor's initial location
    private int _startingX;
    private int _startingY;
    // variable for GifManager
    private GifManager _gifManager;

    public ScreensaverForm()
    {
        InitializeComponent();
        // initialize GifManager object
        _gifManager = new GifManager();
        // call loading of the pictures
        _gifManager.LoadGifs();
        // set cursor;s initial location
        _startingX = Cursor.Position.X;
        _startingY = Cursor.Position.Y;
        // gets rid of top bar and borders of the app
        FormBorderStyle = FormBorderStyle.None;
        // forces displaying the app over all other apps
        TopMost = true;
        // sets picture size to PictureBox size
        pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
        // set PictureBox size to form size
        pictureBox.Dock = DockStyle.Fill;
        // set the time interval between ticks
        timerActivator.Interval = 3000;
        // by default, the screensaver is off
        WindowState = FormWindowState.Minimized;
        // start the timer
        timerActivator.Start();
    }

    private void timerActivator_Tick(object sender, EventArgs e)
    {
        // change pictureBox image to randomly chosen one by GifManager
        pictureBox.Image = _gifManager.RandomPicture();
        // activating the screensaver
        WindowState = FormWindowState.Maximized;
        // this call forces focus on the aplication window
        // without this, the events may not work properly
        Activate();
        // stop the timer
        timerActivator.Stop();
    }

    private void Form1_KeyPress(object sender, KeyPressEventArgs e)
    {
        /* to determine which key was pressed
         * use arguments given by the event
         * ESC key code is 27
         */
        if (e.KeyChar == 27)
        {
            Application.Exit();
        }
        // if the screensaver is active...
        if (WindowState == FormWindowState.Maximized)
        {
            // ...deactivate it
            WindowState = FormWindowState.Minimized;
            // start the activator
            timerActivator.Start();
        }
    }

    private void pictureBox1_Click(object sender, EventArgs e)
    {
        // if the screensaver is active...
        if (WindowState == FormWindowState.Maximized)
        {
            // ...deactivate it
            WindowState = FormWindowState.Minimized;
            // start the activator
            timerActivator.Start();
        }
    }

    private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
    {
        // if the screensaver is active
        if (WindowState == FormWindowState.Maximized)
        {
            // calculate the difference between initial and current cursor location
            int xDiff = _startingX - e.X;
            int yDiff = _startingY - e.Y;
            /*
             * Let's consider the mouse moved, only when
             * the absolute value is bigger than some value
             * for example 10 for x or y.
             * This allows us to give us more control
             */
            if (Math.Abs(xDiff) > 10 || Math.Abs(yDiff) > 10)
            {
                // deactivate it
                WindowState = FormWindowState.Minimized;
                // start the activator
                timerActivator.Start();
                // and set new starting coordinates
                _startingX = e.X;
                _startingY = e.Y;
            }
        }
    }
}