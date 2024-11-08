# ESPHome Custom Components

This repository hosts custom ESPHome components for various sensors and devices. It includes a custom `PlaatoAirlock` component that allows for the integration of Plaato Airlock fermentation sensors, providing real-time temperature and bubble count data for brewing applications.

## Components

### PlaatoAirlock
The `PlaatoAirlock` component is designed to interface with a Plaato Airlock fermentation sensor, giving detailed insights into temperature and bubble count (representing CO₂ release). These metrics are essential for homebrewers and fermentation enthusiasts who want to track and optimize their fermentation processes.

- **Temperature**: Tracks the current temperature measured by the sensor.
- **Bubble Count**: Tracks CO₂ release, with bubble rate measurements indicating the progress of fermentation.

## Installation

1. Clone this repository into your ESPHome configuration’s `external_components` directory or add it as a GitHub source.
2. Reference the desired component (e.g., `PlaatoAirlock`) in your ESPHome YAML file.
3. Configure the required sensors and polling intervals as desired.
