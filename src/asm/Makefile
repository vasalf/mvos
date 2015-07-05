SRCS=$(wildcard *.s)
OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.s=.o))

all: $(OBJS)

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	$(AS) $(ASLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

.PHONY: all clean
