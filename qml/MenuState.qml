pragma Singleton
import QtQuick

QtObject {
    // Core menu state
    property string currentMenuId: "closed"
    property var menuHistory: []

    // Confirm state
    property string confirmText: ""
    property var confirmAction: null
    property var cancelAction: null

    signal menuChanged()
    signal showConfirmDialog()

    readonly property var menuRegistry: ({
                                             closed: {
                                                 id: "closed",
                                                 header: "",
                                                 icon: "menu",
                                                 component: null
                                             },
                                             main: {
                                                 id: "main",
                                                 header: "CAR-BT-HMI",
                                                 icon: "close",
                                                 component: null
                                             },
                                             device: {
                                                 id: "device",
                                                 header: "Pair Device",
                                                 icon: "back-left",
                                                 component: null
                                             },
                                             obd: {
                                                 id: "obd",
                                                 header: "OBD PIDs",
                                                 icon: "back-left",
                                                 component: null
                                             },
                                             settings: {
                                                 id: "settings",
                                                 header: "Settings",
                                                 icon: "back-left",
                                                 component: null
                                             },
                                             info: {
                                                 id: "info",
                                                 header: "Device Info",
                                                 icon: "back-left",
                                                 component: null
                                             },
                                             confirm: {
                                                 id: "confirm",
                                                 header: "Confirm",
                                                 icon: "back-left",
                                                 component: null
                                             }
                                         })

    function registerComponent(id, component) {
        if (menuRegistry[id])
            menuRegistry[id].component = component
    }

    function switchTo(menuId) {
        if (!menuRegistry[menuId]) {
            console.warn("Unknown menu ID:", menuId)
            return
        }

        if (menuId === "closed") {
            menuHistory = []
        }

        else if (currentMenuId !== "confirm" && currentMenuId !== "closed" && currentMenuId !== menuId) {
            menuHistory.push(currentMenuId)
        }

        currentMenuId = menuId
        menuChanged()
    }

    function goBack() {
        if (menuHistory.length > 0) {
            let previous = menuHistory.pop()
            currentMenuId = previous
            menuChanged()
        } else {
            switchTo("main")
        }
    }

    function showConfirm(text, confirmFn, cancelFn) {
        confirmText = text
        confirmAction = confirmFn
        cancelAction = cancelFn
        switchTo("confirm")
        showConfirmDialog()
    }

    function clearConfirm() {
        confirmText = ""
        confirmAction = null
        cancelAction = null
    }
}
