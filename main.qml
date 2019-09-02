import QtQuick 2.13
import QtQuick.Window 2.13
import QtCharts 2.3

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ChartView {
        id: plot
        title: "Plot"
        anchors.fill: parent
        antialiasing: true

        SplineSeries {
            objectName: "series"
        }
    }
}
