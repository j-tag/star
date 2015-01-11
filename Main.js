/* Main Javascript file for handling main page options */

/* Backgrounds */

// Background image easing type
var bgEasingType = Easing.OutQuad

// Background change duration
var bgDuration = 1114

/* Messagebox */

// Messagebox show duration
var msgShowDuration = 500

// Message box easing type
var msgEasingType = Easing.InOutQuad

/* Pages */

// Page easing type
var pageEasingType = Easing.OutExpo

// Page rollback duration
var pageDuration = 1400

// Page color
var pageColor = "#e4e4e4"

// Page border radius
var pageRadius = 3

// Page opacity
var pageOpacity = .7

/* Flipper */

// Flipper Easing type
var flipEasingType = Easing.OutBack

// Flipper flip duration
var flipDuration = pageDuration

// This function will change background image of main home
function changeBackground()
{
    if(imgBackground.opacity === 1)
    {
        imgBackground.opacity = 0
        imgBackground2.opacity = 1
        imgBackground3.opacity = 0
    }
    else if(imgBackground2.opacity === 1)
    {
        imgBackground.opacity = 0
        imgBackground2.opacity = 0
        imgBackground3.opacity = 1
    }
    else if(imgBackground3.opacity === 1)
    {
        imgBackground.opacity = 1
        imgBackground2.opacity = 0
        imgBackground3.opacity = 0
    }


    console.log("Background changed")
}

// This function will disable all page instead of one page that gets from parameter
function disablePages(except_item)
{
    home.enabled =  except_item === home
    todayHolidays.enabled =  except_item === todayHolidays
}

// Show a nice and neat blur message box
function showMessage(message)
{
    // Disable toolbar
    mainWindow.toolBar.enabled = false
    // Disable main content
    mainContent.enabled = false
    // Set message details
    glassMessage.strMessage = message
    glassMessage.mainContent = mainContent
    glassMessage.blurContent = msgBlur
    // Show blur effect
    msgBlur.opacity = 1
    // Show message dialog
    glassMessage.opacity = 1
}
