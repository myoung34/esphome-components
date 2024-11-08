import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY

plaato_airlock_ns = cg.esphome_ns.namespace("plaato_airlock")
PlaatoAirlock = plaato_airlock_ns.class_(
    "PlaatoAirlock", cg.PollingComponent
)

CONF_TEMP_SENSOR = "temp_sensor"
CONF_BUBBLE_SENSOR = "bubble_sensor"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(PlaatoAirlock),
        cv.Optional(CONF_TEMP_SENSOR): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY, icon=ICON_EMPTY, accuracy_decimals=1
        ),
        cv.Optional(CONF_BUBBLE_SENSOR): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY, icon=ICON_EMPTY, accuracy_decimals=1
        ),
    }
).extend(cv.polling_component_schema("1s"))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if temp_sensor_config := config.get(CONF_TEMP_SENSOR):
        sens = await sensor.new_sensor(temp_sensor_config)
        cg.add(var.set_temp_sensor(sens))

    if bubble_sensor_config := config.get(CONF_BUBBLE_SENSOR):
        sens = await sensor.new_sensor(bubble_sensor_config)
        cg.add(var.set_bubble_sensor(sens))
