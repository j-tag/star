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

// Message box rectangle easing type
var msgRectEasingType = Easing.InOutExpo

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

/* Texts */

// Default text color
const textColor = "#333"

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
}

// This function will disable all page instead of one page that gets from parameter
function disablePages(except_item)
{
    home.enabled = except_item === home
    todayHolidays.enabled = except_item === todayHolidays
    todayTasksPage.enabled = except_item === todayTasksPage
}

// This function will change current item of main stack view
function changePage(targetItem) {

    if(stack.busy) {
        return
    }

    if(stack.currentItem === targetItem) {
        changeBackground()
        return
    }

    stack.replace(targetItem)

    disablePages(targetItem)
    changeBackground()
}

// Show a nice and neat blur message box
function showMessage(message)
{
    // Disable toolbar
    mainWindow.header.enabled = false
    // Disable main content
    mainContent.enabled = false
    // Set message details
    glassMessage.strMessage = message
    glassMessage.mainContent = mainContent
    glassMessage.blurContent = msgBlur
    // Show blur effect
    msgBlur.opacity = 1
    glassMessage.show()
}

// Show a nice and neat blur login box
function showLoginPopup()
{
    // Disable toolbar
    mainWindow.header.enabled = false
    // Disable main content
    mainContent.enabled = false
    // Set message details
    loginGlassMessage.mainContent = mainContent
    loginGlassMessage.blurContent = msgBlur
    // Show blur effect
    msgBlur.opacity = 1
    loginGlassMessage.show()
}

// Show a nice and neat blur progress indicator message
function showGlassProgressMessage() {

    // Disable toolbar
    mainWindow.header.enabled = false
    // Disable main content
    mainContent.enabled = false
    // Set message details
    glassProgressMessage.mainContent = mainContent
    glassProgressMessage.blurContent = msgBlur
    // Show blur effect
    msgBlur.opacity = 1
    glassProgressMessage.show()
}

// Flip main content to setup wizard
function toggleFlipToSetupWizard() {
    setupWizard.active = true
    flipableMainWindow.flipped = !flipableMainWindow.flipped
}

// Flip setup wizard to main content
function toggleFlipToMainContent() {
    setupWizard.active = false
    flipableMainWindow.flipped = !flipableMainWindow.flipped
}

// Show a task
function showTask(id, title, description, triggerDate, triggerTime, createdAt, updatedAt) {
    // Disable toolbar
    mainWindow.header.enabled = false
    // Disable main content
    mainContent.enabled = false
    // Set message details
    glassTaskCardView.mainContent = mainContent
    glassTaskCardView.blurContent = msgBlur
    glassTaskCardView.modelId = id
    glassTaskCardView.title = title
    glassTaskCardView.description = description
    glassTaskCardView.triggerDate = triggerDate
    glassTaskCardView.triggerTime = triggerTime
    glassTaskCardView.createdAt = createdAt
    glassTaskCardView.updatedAt = updatedAt

    // Show blur effect
    msgBlur.opacity = 1
    glassTaskCardView.show()
}

// Show edit task dialog
function showEditTask(id, title, description, triggerDate, triggerTime, createdAt, updatedAt) {
    // Disable toolbar
    mainWindow.header.enabled = false
    // Disable main content
    mainContent.enabled = false
    // Set message details
    glassTaskCardEdit.mainContent = mainContent
    glassTaskCardEdit.blurContent = msgBlur
    glassTaskCardEdit.modelId = id
    glassTaskCardEdit.title = title
    glassTaskCardEdit.description = description
    glassTaskCardEdit.triggerDate = triggerDate
    glassTaskCardEdit.triggerTime = triggerTime
    glassTaskCardEdit.createdAt = createdAt
    glassTaskCardEdit.updatedAt = updatedAt

    glassTaskCardEdit.placeTextFieldValues()

    // Show blur effect
    msgBlur.opacity = 1
    glassTaskCardEdit.show()
}

// Edit a task
function editTask(id, title, description, triggerDate, triggerTime) {
    const timestampTriggerDate = triggerDate === -1 ? -1 : jalaliDate.jalaliToUnixTimestamp(triggerDate)
    todayTasks.editTask(id, title, description, timestampTriggerDate, triggerTime)
}

// Delete a task
function deleteTask(id) {
    todayTasks.deleteTask(id)
}

// Convert an English number to Persian variation
function englishNumberToPersian(number) {

    if(number !== 0 && !number) {
        return number
    }

    return number.toString().replace(/0/g, "۰").
    replace(/1/g, "۱").replace(/2/g, "۲").replace(/3/g, "۳").
    replace(/4/g, "۴").replace(/5/g, "۵").replace(/6/g, "۶").
    replace(/7/g, "۷").replace(/8/g, "۸").replace(/9/g, "۹")

}

// Convert a Persian number to English variation
function persianNumberToEnglish(number) {

    if(number !== 0 && !number) {
        return number
    }

    return number.toString().replace(/۰/g, "0").
    replace(/۱/g, "1").replace(/۲/g, "2").replace(/۳/g, "3").
    replace(/۴/g, "4").replace(/۵/g, "5").replace(/۶/g, "6").
    replace(/۷/g, "7").replace(/۸/g, "8").replace(/۹/g, "9")

}
