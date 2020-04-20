#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <vector>
#include <string>
#include "qcustomplot.h"

namespace Ui {
class Form;
}

class GraphWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit GraphWindow(QWidget *parent = nullptr);

    ~GraphWindow();
    void addGraph(const std::string& name, const std::string& color, const std::vector<double>& x, const std::vector<double>& y);
    void setXAxisRange(double start, double end);
    void setYAxisRange(double start, double end);
    void setTitle(const std::string& graph_title);
private:
    Ui::Form *ui;
};



#endif // GRAPHWINDOW_H
