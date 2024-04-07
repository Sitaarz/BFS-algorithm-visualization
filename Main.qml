import QtQuick
import QtQuick.Controls
import BFS
import QtQuick.Layouts

Window {
    width: 1000
    height: 800
    visible: true
    title: qsTr("BFS Visualisation")
    color: palette.base

    RowLayout{
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10
        Column{
            spacing: 2
            Text{
                color: "white"
                text:"Grid dimension(3 to 6)"
            }
            TextField {
                id: cols_rows_field
                placeholderText: "Press enter"
                validator: IntValidator {bottom: 3; top: 6;}
                onAccepted: {
                    BFS.startReset()
                    searchButton.enabled = true
                    BFS.receivedInt = parseInt(text)
                }
            }
        }
        Column{
            spacing: 2
        Text{
            color: "white"
            text: "Start node number."
            }
        TextField {
            id: startItemField
            placeholderText: "Press enter"
            validator: IntValidator {bottom: 0; top: BFS.rows*BFS.cols-1;}
            onAccepted: {
                BFS.startReset()
                searchButton.enabled = true
                BFS.startNodeId = parseInt(text)
            }
        }
        }
        Column{
            spacing: 2
            Text{
                color: "white"
                text: "End node number"
            }
            TextField {
                id: endItemField
                placeholderText: "Press enter"
                validator: IntValidator {bottom: 0; top: BFS.rows*BFS.cols-1;}
                onAccepted: {
                    BFS.startReset()
                    searchButton.enabled = true
                    BFS.endNodeId = parseInt(text)
                }
            }
        }
    }

    RowLayout {
        width: 500
        height:200
        spacing: 0
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            color:palette.base
                width:250
                height: 100
                Button {
                    id: searchButton
                    width:100
                    height:80
                    anchors.centerIn: parent
                    text: "Start searching"
                    onClicked: {
                        BFS.startSearch()
                        searchButton.enabled = false
                    }
                }
            }
            Rectangle {
                color:palette.base
                    width:250
                    height: 100
                Button {
                    id: resetButton
                    enabled: true
                    width:100
                    height:80
                    anchors.centerIn: parent
                    text: "Reset"
                    onClicked: {
                        BFS.startReset()
                        searchButton.enabled = true
                    }
                }
            }

    }

    Grid{
        id: grid
        // anchors.fill: parent
        anchors.centerIn: parent
        columns: BFS.cols
        rows: BFS.rows
        spacing: 2

        Repeater {
            id: repeater
            model: BFS.rows * BFS.cols

            delegate: Rectangle {
                width: 80
                height: 80
                color: {
                    let isVisited = BFS.graph[index]
                    return isVisited ?  "goldenrod" : "wheat"
                        }
                Text {
                    text: index
                    font.family: "Helvetica"
                    font.pointSize: 24
                    color: "black"
                    anchors.centerIn: parent
                }
                MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                BFS.changeColor(index, !BFS.graph[index]);
                            }
                        }
                HoverHandler {
                        id: mouse
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                        cursorShape: Qt.PointingHandCursor
                    }
            }
        }
    }
}
