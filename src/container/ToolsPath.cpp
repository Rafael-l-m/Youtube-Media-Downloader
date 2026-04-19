
#include "container/ToolsPath.hpp"

namespace CONTAINER {
    // Public

    ToolsPath::ToolsPath() : yt_dlp_path(QString()), ffmpeg_path(QString()), node_js_path(QString()) {}

    ToolsPath::ToolsPath(QString yt_dlp_path, QString ffmpeg_path, QString node_js_path) : yt_dlp_path(std::move(yt_dlp_path)), ffmpeg_path(std::move(ffmpeg_path)), node_js_path(std::move(node_js_path)) {}

    ToolsPath::ToolsPath(const ToolsPath &other) : yt_dlp_path(other.yt_dlp_path), ffmpeg_path(other.ffmpeg_path), node_js_path(other.node_js_path) {}

    QString ToolsPath::getYtDlpPath() {QMutexLocker locker(&this->mutex); return this->yt_dlp_path;}

    QString ToolsPath::getFFmpegPath() {QMutexLocker locker(&this->mutex); return this->ffmpeg_path;}

    QString ToolsPath::getNodePath() {QMutexLocker locker(&this->mutex); return this->node_js_path;}

    void ToolsPath::setYtDlpPath(const QString& ytDlpPath) {QMutexLocker locker(&this->mutex); this->yt_dlp_path = ytDlpPath;}

    void ToolsPath::setFFmpegPath(const QString& ffmpegPath) {QMutexLocker locker(&this->mutex); this->ffmpeg_path = ffmpegPath;}

    void ToolsPath::setNodePath(const QString& nodePath) {QMutexLocker locker(&this->mutex); this->node_js_path = nodePath;}

    void ToolsPath::setAll(const ToolsPath& toolsPath) {
        this->setYtDlpPath(toolsPath.yt_dlp_path);
        this->setFFmpegPath(toolsPath.ffmpeg_path);
        this->setNodePath(toolsPath.node_js_path);
    }
}
