#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setFixedSize(this->width(), this->height());
  loadSetting();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_backgroundColorQPushButton_clicked() {
  QColor currentColor =
      ui->backgroundColorQPushButton->palette().color(QPalette::Button);
  QColor color = QColorDialog::getColor(currentColor, this, "Pick color");

  if (color.isValid()) {
    ui->backgroundColorQPushButton->setStyleSheet("background-color: " +
                                                  color.name());
    ui->openGLWidget->setBackgroundColor(color.redF(), color.greenF(),
                                         color.blueF());
    ui->openGLWidget->update();
  }
}

void MainWindow::on_edgeColorQPushButton_clicked() {
  QColor currentColor =
      ui->edgeColorQPushButton->palette().color(QPalette::Button);
  QColor color = QColorDialog::getColor(currentColor, this, "Pick color");

  if (color.isValid()) {
    ui->edgeColorQPushButton->setStyleSheet("background-color: " +
                                            color.name());
    ui->openGLWidget->setEdgeColor(color.redF(), color.greenF(), color.blueF());
    ui->openGLWidget->update();
  }
}

void MainWindow::on_vertexColorQPushButton_clicked() {
  QColor currentColor =
      ui->vertexColorQPushButton->palette().color(QPalette::Button);
  QColor color = QColorDialog::getColor(currentColor, this, "Pick color");

  if (color.isValid()) {
    ui->vertexColorQPushButton->setStyleSheet("background-color: " +
                                              color.name());
    ui->openGLWidget->setVertexColor(color.redF(), color.greenF(),
                                     color.blueF());
    ui->openGLWidget->update();
  }
}

void MainWindow::on_selectFileQPushButton_clicked() {
  QSettings settings("21SQUAD", "3DViewer");
  settings.clear();
  settings.sync();

  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open 3D Model"), "", tr("OBJ Files (*.obj);;All Files (*)"));
  if (!fileName.isEmpty()) {
    ui->openGLWidget->resetTransformationValues();
    resetSliders();

    QFileInfo fileInfo(fileName);

    s21::ObjectController& open_gl_controller =
        ui->openGLWidget->getController();
    if (open_gl_controller.InitializeObject(fileName.toStdString().c_str()) ==
        s21::RETURN_NORMAL) {
      ui->fileSelectedQLineEdit->setText(fileName);
      ui->fileNameQLineEdit->setText(fileInfo.fileName());
      ui->edgesCountQLineEdit->setText(
          QString::number(open_gl_controller.GetEdges().size()));
      ui->vertexCountQLineEdit->setText(
          QString::number(open_gl_controller.GetVertices().size()));
      ui->openGLWidget->update();
    }
  }
}

void MainWindow::saveSettings() {
  QSettings settings("21SQUAD", "3DViewer");

  Color vertex_color = ui->openGLWidget->getVertexColor();
  settings.setValue("vertexColorRed", vertex_color.red);
  settings.setValue("vertexColorGreen", vertex_color.green);
  settings.setValue("vertexColorBlue", vertex_color.blue);

  Color edge_color = ui->openGLWidget->getEdgeColor();
  settings.setValue("edgeColorRed", edge_color.red);
  settings.setValue("edgeColorGreen", edge_color.green);
  settings.setValue("edgeColorBlue", edge_color.blue);

  double vertices_size = ui->openGLWidget->getVerticesSize();
  double edges_thickness = ui->openGLWidget->getEdgesThickness();
  settings.setValue("verticesSize", vertices_size);
  settings.setValue("edgeThickness", edges_thickness);

  int projection_type = ui->openGLWidget->getProjectionType();
  int edges_type = ui->openGLWidget->getEdgesType();
  int vertex_display_type = ui->openGLWidget->getVertexDisplayType();
  settings.setValue("projectionType", projection_type);
  settings.setValue("edgesType", edges_type);
  settings.setValue("vertexDisplayType", vertex_display_type);
}

void MainWindow::loadSetting() {
  QSettings settings("21SQUAD", "3DViewer");
  loadVertexColor(settings);
  loadEdgeColor(settings);
  loadSizeAndThickness(settings);
  loadProjectionType(settings);
  loadEdgesType(settings);
  loadVertexDisplayType(settings);
}

void MainWindow::resetSliders() {
  ui->xTranslateQSlider->setValue(0);
  ui->yTranslateQSlider->setValue(0);
  ui->zTranslateQSlider->setValue(0);

  ui->xRotateQSlider->setValue(0);
  ui->yRotateQSlider->setValue(0);
  ui->zRotateQSlider->setValue(0);

  ui->scaleQSlider->setValue(100);
}

void MainWindow::loadVertexColor(const QSettings& settings) {
  QColor vertex_color;
  vertex_color.setRedF(settings.value("vertexColorRed").toFloat());
  vertex_color.setGreenF(settings.value("vertexColorGreen").toFloat());
  vertex_color.setBlueF(settings.value("vertexColorBlue").toFloat());
  ui->openGLWidget->setVertexColor(vertex_color.redF(), vertex_color.greenF(),
                                   vertex_color.blue());
  ui->vertexColorQPushButton->setStyleSheet("background-color: " +
                                            vertex_color.name());
}

void MainWindow::loadEdgeColor(const QSettings& settings) {
  QColor edge_color;
  edge_color.setRedF(settings.value("edgeColorRed").toFloat());
  edge_color.setGreenF(settings.value("edgeColorGreen").toFloat());
  edge_color.setBlueF(settings.value("edgeColorBlue").toFloat());
  ui->openGLWidget->setEdgeColor(edge_color.redF(), edge_color.greenF(),
                                 edge_color.blueF());
  ui->edgeColorQPushButton->setStyleSheet("background-color: " +
                                          edge_color.name());
}

void MainWindow::loadSizeAndThickness(const QSettings& settings) {
  ui->openGLWidget->setVerticesSize(settings.value("verticesSize").toDouble());
  ui->vertexSizeQSlider->setValue(ui->openGLWidget->getVerticesSize());
  ui->openGLWidget->setEdgesThickness(
      settings.value("edgeThickness").toDouble());
  ui->thicknessQSlider->setValue(ui->openGLWidget->getEdgesThickness());
}

void MainWindow::loadProjectionType(const QSettings& settings) {
  ui->openGLWidget->setProjectionType(
      settings.value("projectionType", 0).toInt());
  if (ui->openGLWidget->getProjectionType() == 0) {
    ui->perspectiveQRadioButton->setChecked(true);
  } else {
    ui->orthographicQRadioButton->setChecked(true);
  }
}

void MainWindow::loadEdgesType(const QSettings& settings) {
  ui->openGLWidget->setEdgesType(settings.value("edgesType", 0).toInt());
  if (ui->openGLWidget->getEdgesType() == 0) {
    ui->solidQRadioButton->setChecked(true);
  } else {
    ui->dashedQRadioButton->setChecked(true);
  }
}

void MainWindow::loadVertexDisplayType(const QSettings& settings) {
  ui->openGLWidget->setVertexDisplayType(
      settings.value("vertexDisplayType").toInt());
  if (ui->openGLWidget->getVertexDisplayType() == 0) {
    ui->noneVertexQRadioButton->setChecked(true);
  } else if (ui->openGLWidget->getVertexDisplayType() == 1) {
    ui->circleVertexQRadioButton->setChecked(true);
  } else {
    ui->squareVertexQRadioButton->setChecked(true);
  }
}

void MainWindow::on_noneVertexQRadioButton_clicked() {
  ui->openGLWidget->setVertexDisplayType(0);
  ui->openGLWidget->update();
}

void MainWindow::on_circleVertexQRadioButton_clicked() {
  ui->openGLWidget->setVertexDisplayType(1);
  ui->openGLWidget->update();
}

void MainWindow::on_squareVertexQRadioButton_clicked() {
  ui->openGLWidget->setVertexDisplayType(2);
  ui->openGLWidget->update();
}

void MainWindow::on_solidQRadioButton_clicked() {
  ui->openGLWidget->setEdgesType(0);
  ui->openGLWidget->update();
}

void MainWindow::on_dashedQRadioButton_clicked() {
  ui->openGLWidget->setEdgesType(1);
  ui->openGLWidget->update();
}

void MainWindow::on_perspectiveQRadioButton_clicked() {
  ui->openGLWidget->setProjectionType(0);
  ui->openGLWidget->update();
}

void MainWindow::on_orthographicQRadioButton_clicked() {
  ui->openGLWidget->setProjectionType(1);
  ui->openGLWidget->update();
}

void MainWindow::on_vertexSizeQSlider_valueChanged(int value) {
  ui->openGLWidget->setVerticesSize(value);
  ui->openGLWidget->update();
}

void MainWindow::on_thicknessQSlider_valueChanged(int value) {
  ui->openGLWidget->setEdgesThickness(value);
  ui->openGLWidget->update();
}

void MainWindow::on_xTranslateQSlider_valueChanged(int value) {
  double translation_value = value - ui->openGLWidget->getObjectTranslate().x;
  translation_value *= ui->openGLWidget->getController().GetMaxVertex() / 100;
  ui->openGLWidget->setObjectTranslateX(value);
  ui->openGLWidget->getController().MoveByX(translation_value);
  ui->openGLWidget->update();
}

void MainWindow::on_yTranslateQSlider_valueChanged(int value) {
  double translation_value = value - ui->openGLWidget->getObjectTranslate().y;
  translation_value *= ui->openGLWidget->getController().GetMaxVertex() / 100;
  ui->openGLWidget->setObjectTranslateY(value);
  ui->openGLWidget->getController().MoveByY(translation_value);
  ui->openGLWidget->update();
}

void MainWindow::on_zTranslateQSlider_valueChanged(int value) {
  double translation_value = value - ui->openGLWidget->getObjectTranslate().z;
  translation_value *= ui->openGLWidget->getController().GetMaxVertex() / 100;
  ui->openGLWidget->setObjectTranslateZ(value);
  ui->openGLWidget->getController().MoveByZ(translation_value);
  ui->openGLWidget->update();
}

void MainWindow::on_xRotateQSlider_valueChanged(int value) {
  double rotation_value = value - ui->openGLWidget->getObjectRotation().x;
  ui->openGLWidget->getController().RotateByX(rotation_value);
  ui->openGLWidget->setObjectRotationX(value);
  ui->openGLWidget->update();
}

void MainWindow::on_yRotateQSlider_valueChanged(int value) {
  double rotation_value = value - ui->openGLWidget->getObjectRotation().y;
  ui->openGLWidget->getController().RotateByY(rotation_value);
  ui->openGLWidget->setObjectRotationY(value);
  ui->openGLWidget->update();
}

void MainWindow::on_zRotateQSlider_valueChanged(int value) {
  double rotation_value = value - ui->openGLWidget->getObjectRotation().z;
  ui->openGLWidget->getController().RotateByZ(rotation_value);
  ui->openGLWidget->setObjectRotationZ(value);
  ui->openGLWidget->update();
}

void MainWindow::on_scaleQSlider_valueChanged(int value) {
  double shift = value / ui->openGLWidget->getObjectScale();
  ui->openGLWidget->getController().Scale(shift);
  ui->openGLWidget->setObjectScale(value);
  ui->openGLWidget->update();
}

void MainWindow::on_pngQPushButton_clicked() {
  QImage image = ui->openGLWidget->grabFramebuffer();
  QString filter = "BMP (*.bmp);;JPEG (*.jpg *.jpeg)";
  QString default_file_name = "untitled";
  QString selected_filter;
  QString file_name = QFileDialog::getSaveFileName(
      this, tr("Save Image"), default_file_name, filter, &selected_filter);

  if (!file_name.isEmpty()) {
    QByteArray format = "JPEG";
    if (selected_filter.startsWith("BMP")) {
      format = "BMP";
    }

    if (QFileInfo(file_name).suffix().isEmpty()) {
      file_name += '.' + format.toLower();
    }

    if (image.save(file_name, format)) {
      QMessageBox::information(this, tr("Success"),
                               tr("The image was successfully saved."));
    } else {
      QMessageBox::critical(this, tr("Failed"),
                            tr("Could not save the image."));
    }
  } else {
    QMessageBox::critical(this, tr("Failed"),
                          tr("Incorrect name or operation cancelled."));
  }
}

void MainWindow::on_gifQPushButton_clicked() {
  gif = new QGifImage(QSize(1000, 1000));
  timerGif = new QTimer(this);

  ui->gifQPushButton->setStyleSheet(
      "border-image: url(:/resources/images/screen_recording.png);");
  connect(timerGif, &QTimer::timeout, this, &MainWindow::gifSelect);

  timerGif->setInterval(100);
  timerGif->start();
}

void MainWindow::gifSelect() {
  QImage image(640, 480, QImage::Format_RGB32);
  image = ui->openGLWidget->grabFramebuffer();
  gif->addFrame(image, 10);
  ++fps;
  if (fps == 50) {
    QString fileName = QFileDialog::getSaveFileName(this, "Gif", "", "(*.gif)");
    timerGif->stop();
    gif->save(fileName);
    QFileInfo check_file(fileName);
    if (check_file.exists())
      QMessageBox::information(NULL, QObject::tr("OK"), tr("Success"));
    else
      QMessageBox::critical(NULL, QObject::tr("Error"), tr("Failed"));
    fps = 0;
    ui->gifQPushButton->setStyleSheet(
        "border-image: url(:/resources/images/screen_record.png);");
    delete gif;
    delete timerGif;
  }
}
