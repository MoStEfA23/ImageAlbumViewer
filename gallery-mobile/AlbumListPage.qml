import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

PageTheme {

    toolbarTitle: "Albums"
    toolbarButtons: ToolButton{
        background: Image {
            source: "qrc:/res/icons/album-add.svg"
        }

        onClicked: {
            newAlbumDialog.open()
        }
    }

    InputDialog{
        id: newAlbumDialog
        title: "new album"
        label: "Album name:"
        hint: "my album"

        onAccepted: {
            albumModel.addAlbumFromName(editText.text)
        }
    }

    ListView{
        id: albumListView
        model: albumModel
        spacing: 5
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent

            onClicked: {
                albumListView.currentIndex = index
                pictureModel.setAlbumId(id)
                pageStack.push("qrc:/qml/AlbumPage.qml", {albumName: name,albumRowIndex: index})
            }
        }

        delegate: Rectangle{
            width: parent.width
            height: 120
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
