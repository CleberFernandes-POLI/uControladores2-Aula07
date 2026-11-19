#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define STACK_SIZE 1024
#define THREAD_PRIORITY 5

#define PEDESTRE_RED_PIN   8 	// Pino PTB8  | LED Vermelho
#define PEDESTRE_GREEN_PIN 9 	// Pino PTB9  | LED Verde
#define PEDESTRE_AMARELO_PIN 10 // Pino PTB10 | LED Amarelo

static const struct device *gpio_port = DEVICE_DT_GET(DT_NODELABEL(gpiob));

K_MUTEX_DEFINE(pedestre_led_mutex);
K_SEM_DEFINE(red_led_permission, 1, 1);
K_SEM_DEFINE(green_led_permission, 0, 1);
K_SEM_DEFINE(amarelo_led_permission, 0, 1);
K_THREAD_STACK_DEFINE(green_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(red_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(amarelo_stack, STACK_SIZE);
static struct k_thread green_thread_data;
static struct k_thread red_thread_data;
static struct k_thread amarelo_thread_data;

static void set_led(gpio_pin_t pin, int value, const char *nome_led)
{
	int ret = gpio_pin_set(gpio_port, pin, value);
	if (ret < 0) {
		printk("Erro ao alterar %s (pino %d): codigo %d\n", nome_led, pin, ret);
	}
}

static void green_led_thread(void *arg1, void *arg2, void *arg3)
{
	ARG_UNUSED(arg1);
	ARG_UNUSED(arg2);
	ARG_UNUSED(arg3);

	printk("Thread 1 do led Verde pronta\n");
	while (1) {
		k_sem_take(&green_led_permission, K_FOREVER);
		if (k_mutex_lock(&pedestre_led_mutex, K_FOREVER) == 0) {
			set_led(PEDESTRE_GREEN_PIN, 1, "VERDE");
			set_led(PEDESTRE_RED_PIN, 0, "VERMELHO");
			set_led(PEDESTRE_AMARELO_PIN, 0, "AMARELO");
			printk("LED Verde acesso\n");
			k_msleep(3000);
			set_led(PEDESTRE_GREEN_PIN, 0, "VERDE");
			k_mutex_unlock(&pedestre_led_mutex);
			k_sem_give(&amarelo_led_permission);
		}
	}
}

static void red_led_thread(void *arg1, void *arg2, void *arg3)
{
	ARG_UNUSED(arg1);
	ARG_UNUSED(arg2);
	ARG_UNUSED(arg3);

	printk("Thread 2 do Vermelho pronta\n");
	while (1) {
		k_sem_take(&red_led_permission, K_FOREVER);
		if (k_mutex_lock(&pedestre_led_mutex, K_FOREVER) == 0) {
			set_led(PEDESTRE_GREEN_PIN, 0, "VERDE");
			set_led(PEDESTRE_RED_PIN, 1, "VERMELHO");
			set_led(PEDESTRE_AMARELO_PIN, 0, "AMARELO");
			printk("LED Vermelho acesso\n");
			k_msleep(4000);
			set_led(PEDESTRE_RED_PIN, 0, "VERMELHO");
			k_mutex_unlock(&pedestre_led_mutex);
			k_sem_give(&green_led_permission);
		}
	}
}

static void amarelo_led_thread(void *arg1, void *arg2, void *arg3)
{
	ARG_UNUSED(arg1);
	ARG_UNUSED(arg2);
	ARG_UNUSED(arg3);

	printk("Thread 3 do Amarelo pronta\n");
	while (1) {
		k_sem_take(&amarelo_led_permission, K_FOREVER);
		if (k_mutex_lock(&pedestre_led_mutex, K_FOREVER) == 0) {
			set_led(PEDESTRE_GREEN_PIN, 0, "VERDE");
			set_led(PEDESTRE_RED_PIN, 0, "VERMELHO");
			set_led(PEDESTRE_AMARELO_PIN, 1, "AMARELO");
			printk("LED Amarelo acesso\n");
			k_msleep(1000);
			set_led(PEDESTRE_AMARELO_PIN, 0, "AMARELO");
			k_mutex_unlock(&pedestre_led_mutex);
			k_sem_give(&red_led_permission);
		}
	}
}

int main(void)
{
	int ret;
	k_msleep(500);
	if (!device_is_ready(gpio_port)) {
		printk("Portas B erro\n");
		return 0;
	}
	printk("Porta B pronta\n");
	ret = gpio_pin_configure(gpio_port, PEDESTRE_GREEN_PIN,
				 GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		printk("Falha no LED Verde\n");
		return 0;
	}
	printk("LED Verde pronto\n");

	ret = gpio_pin_configure(gpio_port, PEDESTRE_RED_PIN,
				 GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		printk("Falha no LED Vermelho");
		return 0;
	}
	printk("LED Vermelho pronto\n");


	ret = gpio_pin_configure(gpio_port, PEDESTRE_AMARELO_PIN,
				 GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		printk("Falha no LED Amarelo");
		return 0;
	}
	printk("LED Amarelo pronto\n");
	
	k_thread_create(&green_thread_data, green_stack, STACK_SIZE,
			green_led_thread, NULL, NULL, NULL,
			THREAD_PRIORITY, 0, K_NO_WAIT);

	k_thread_create(&red_thread_data, red_stack, STACK_SIZE,
			red_led_thread, NULL, NULL, NULL,
			THREAD_PRIORITY, 0, K_NO_WAIT);
	
	k_thread_create(&amarelo_thread_data, amarelo_stack, STACK_SIZE,
			amarelo_led_thread, NULL, NULL, NULL,
			THREAD_PRIORITY, 0, K_NO_WAIT);
	printk("Threads prontas\n");

	return 0;
}
