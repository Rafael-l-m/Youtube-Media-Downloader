
#pragma once

#include <QMutex>
#include <QString>

namespace CONTAINER {
    class ToolsPath final {
    public:
        ToolsPath();
        ToolsPath(QString yt_dlp_path, QString ffmpeg_path, QString node_js_path);
        ToolsPath(const ToolsPath& other);

        QString getYtDlpPath();
        QString getFFmpegPath();
        QString getNodePath();
        void setYtDlpPath(const QString& ytDlpPath);
        void setFFmpegPath(const QString& ffmpegPath);
        void setNodePath(const QString& nodePath);
        void setAll(const ToolsPath& toolsPath);

    private:
        mutable QMutex mutex;

        QString yt_dlp_path;
        QString ffmpeg_path;
        QString node_js_path;
    };
}
