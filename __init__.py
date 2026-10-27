import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_LAMBDA

DOMAIN = "lovy_panel_st7789_i80"

ns = cg.esphome_ns.namespace(DOMAIN)
Panel_ST7789_I80 = ns.class_("Panel_ST7789_I80", cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema({

    cv.GenerateID(): cv.declare_id(Panel_ST7789_I80),
    cv.Optional(CONF_LAMBDA): cv.lambda_,

}).extend(cv.polling_component_schema("1s")).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    # cg.add_library("LovyanGFX", None)
    await cg.register_component(var, config)

    if CONF_LAMBDA in config:
        lambda_expr = await cg.process_lambda(
            config[CONF_LAMBDA],
            [(Panel_ST7789_I80.operator("ptr"), "it")],
            return_type=cg.void
        )
        cg.add(var.set_writer(lambda_expr))
