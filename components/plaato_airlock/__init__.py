import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

CODEOWNERS = ["@myoung34"]
DEPENDENCIES = ["wire"]
MULTI_CONF = True

CONF_PLAATO_AIRLOCK_ID = "plaato_airlock_id"

ICON_THERMOMETER_ALERT = "mdi:thermometer-alert"

plaato_airlock_ns = cg.esphome_ns.namespace("plaato_airlock")
PlaatoAirlockComponent = plaato_airlock_ns.class_(
    "PlaatoAirlockComponent", cg.Component
)

PLAATO_AIRLOCK_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_PLAATO_AIRLOCK_ID): cv.use_id(PlaatoAirlockComponent),
    }
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(PlaatoAirlockComponent),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
