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
    Column {
        height: 200
        width: 600
        spacing: 0
        anchors.horizontalCenter: parent.horizontalCenter

        RowLayout {
            width: 600
            height: 100
            spacing: 0
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                color: palette.base
                width: 200
                height: 50

                Column {
                    width: 100
                    height: 30
                    spacing: 2
                    anchors.centerIn: parent

                    Text {
                        color: "white"
                        text: "Grid dimension (3 to 5)"
                    }

                    TextField {
                        id: cols_rows_field
                        placeholderText: "Press enter"
                        validator: IntValidator { bottom: 3; top: 5; }
                        onAccepted: {
                            BFS.startReset()
                            searchButton.enabled = true
                            BFS.receivedInt = parseInt(text)
                        }
                    }
                }
            }

            Rectangle {
                color: palette.base
                width: 200
                height: 50

                Column {
                    width: 100
                    height: 30
                    spacing: 2
                    anchors.centerIn: parent
                    Text {
                        color: "white"
                        text: "Start node number"
                    }

                    TextField {
                        id: startItemField
                        placeholderText: "Press enter"
                        validator: IntValidator { bottom: 0; top: BFS.rows*BFS.cols - 1; }
                        onAccepted: {
                            BFS.startReset()
                            searchButton.enabled = true
                            BFS.startNodeId = parseInt(text)
                        }
                    }
                }
            }

            Rectangle {
                color: palette.base
                width: 200
                height: 50

                Column {
                    anchors.centerIn: parent
                    width: 100
                    height: 30
                    spacing: 2

                    Text {
                        color: "white"
                        text: "End node number"
                    }

                    TextField {
                        id: endItemField
                        placeholderText: "Press enter"
                        validator: IntValidator { bottom: 0; top: BFS.rows*BFS.cols - 1; }
                        onAccepted: {
                            BFS.startReset()
                            searchButton.enabled = true
                            BFS.endNodeId = parseInt(text)
                        }
                    }
                }
            }
        }

        RowLayout {
            width: 600
            height: 100
            spacing: 0
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                color: palette.base
                width: 200
                height: 50

                Button {
                    id: searchButton
                    width: 100
                    height: 30
                    anchors.centerIn: parent
                    text: "Start searching"
                    onClicked: {
                        BFS.startSearch()
                        showPath.enabled = true
                        searchButton.enabled = false
                    }
                }
            }

            Rectangle {
                color: palette.base
                width: 200
                height: 50

                Button {
                    id: showPath
                    enabled: false
                    width: 100
                    height: 30
                    anchors.centerIn: parent
                    text: "Show path"
                    onClicked: {
                        BFS.showShortestPath()
                        showPath.enabled = false
                    }
                }
            }

            Rectangle {
                color: palette.base
                width: 200
                height: 50

                Button {
                    id: resetButton
                    enabled: true
                    width: 100
                    height: 30
                    anchors.centerIn: parent
                    text: "Reset"
                    onClicked: {
                        BFS.startReset()
                        showPath.enabled = false
                        searchButton.enabled = true
                    }
                }
            }
        }
    }


    Grid{
        topPadding: 100
        id: grid
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

            }
        }
    }
}
