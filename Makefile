project:./src/show_bmp.c ./src/get_input.c ./src/main.c ./src/album.c ./src/display.c ./src/font.c ./src/uart.c ./src/smoke_monitor.c ./src/env_monitor.c
	@arm-linux-gcc $^ -o ./bin/main -I ./inc -lpthread