import QtQuick
import QtQuick.Controls
import BFS

Window {
    width: 1000
    height: 800
    visible: true
    title: qsTr("BFS Visualisation")

    Button {
        text: "Ok"
        onClicked: {
        BFS.startSearch();
        }
    }

    Grid{
        id: grid
        // anchors.fill: parent
        anchors.centerIn: parent
        columns: BFS.cols
        rows: BFS.rows
        spacing: 2
        horizontalItemAlignment: Grid.AlignHCenter
        verticalItemAlignment: Grid.AlignVCenter


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

            Connections {
                        target: BFS
                        onColorChanged: {

                                repeater.itemAt(index).color = newColor ? "goldenrod" : "wheat"; // Zmiana koloru na podstawie nowej wartości

                        }
                }

        }

    }

}
