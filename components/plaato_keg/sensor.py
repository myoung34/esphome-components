import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

DEPENDENCIES = []

plaato_keg_ns = cg.esphome_ns.namespace("plaato_keg")
PlaatoKeg = plaato_keg_ns.class_(
    "PlaatoKeg", cg.PollingComponent
)

CONF_TEMP_SENSOR = "temp_sensor"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(PlaatoKeg),
        cv.Optional(CONF_TEMP_SENSOR): sensor.sensor_schema(
            unit_of_measurement="°C", icon="mdi:thermometer", accuracy_decimals=1
        ),
    }
).extend(cv.polling_component_schema("1s"))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # Handle temp sensor
    if temp_sensor_config := config.get(CONF_TEMP_SENSOR):
        sens = await sensor.new_sensor(temp_sensor_config)
        cg.add(var.set_temp_sensor(sens))

