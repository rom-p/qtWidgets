# qtWidgets
this is a small collection of custom Qt widgets.  Included here are:
* QAnimatedTimer -- a "hourglass"-like animation that displays time elapsed and can automatically change its color at predefined time
![QAnimatedTimer screenshot](https://raw.githubusercontent.com/rom-p/qtWidgets/master/doc/atimer.gif)
* QVUMeter -- a vertical VU Meter (or volume meter) that one can see on professional or semi-professional audio hardware

## using in a project
these controls can be independently added to your project.  Just #include the header and make sure the relevant .cpp file is compiled as part of your project.  There are no external dependencies, other than Qt itself

## sample app
the sample application is included: look under sampleApp directory
