#include <qdebug.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <iostream>
#include <QString>
#include <KDE/KCmdLineArgs>
#include <KDE/KCmdLineOptions>


int main(int argc, char *argv[])
{

    KCmdLineArgs::init(argc, argv, "batchTagger", "batchTagger", ki18n("batchTagger"), "0.0");

    KCmdLineOptions options;
    options.add("t <title>");
    options.add("a <artist>");
    options.add("l <album>");
    options.add("r <tracknr>");
    options.add("+file...");

    KCmdLineArgs::addCmdLineOptions(options);

    KCmdLineArgs* args = KCmdLineArgs::parsedArgs();

    bool print_tags_only = false;

    if (!args->isSet("t") & !args->isSet("a") & !args->isSet("l") & !args->isSet("r")){
        print_tags_only = true;
    }

    std::string title = args->getOption("t").toUtf8().data();
    std::string artist = args->getOption("a").toUtf8().data();
    std::string album = args->getOption("l").toUtf8().data();
    QString tracknr = args->getOption("r");

    bool track_ok = false;
    uint track = 0;

    if (args->isSet("r")) {
        track = tracknr.toUInt(&track_ok);
        if (!track_ok) {
            qWarning() << "Could not convert " << tracknr << "to uint. Not Updating Track Number";
        }
    }

    for (int i = 0; i < args->count(); i++) {
        QByteArray ba = args->arg(i).toLocal8Bit();
        TagLib::FileRef f(ba.data());
        TagLib::Tag* tag = f.tag();

        if (print_tags_only){
            std::cout << "File: " << args->arg(i).toLocal8Bit().data() << std::endl;
            std::cout << "Title: " << tag->title() << std::endl;
            std::cout << "Artist: " << tag->artist() << std::endl;
            std::cout << "Album: " << tag->album() << std::endl;
            std::cout << "Track Number: " << tag->track() << std::endl;
            std::cout << std::endl;
            continue;
        }

        if (!title.empty()){
            tag->setTitle(title);
        }

        if (!artist.empty()) {
            tag->setArtist(artist);
        }

        if (!album.empty()) {
            tag->setAlbum(album);
        }

        if (track_ok){
            tag->setTrack(track);
        }

        if (!f.save()) {
            qWarning("Could not save file!");
        }
    }

    return 0;
}
