SRCS=$(wildcard *.c)
OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(OBJS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

.PHONY: all clean
