#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * close_elf - closes an ELF file descriptor
 * @fd: file descriptor to close
 */
void close_elf(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(98);
	}
}

/**
 * check_elf - checks if a file is an ELF file
 * @header: ELF header buffer
 */
void check_elf(unsigned char *header)
{
	if (header[0] != 0x7f || header[1] != 'E' ||
		header[2] != 'L' || header[3] != 'F')
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
		exit(98);
	}
}

/**
 * get_value - gets a value from the ELF header
 * @header: ELF header buffer
 * @offset: offset of the value
 * @size: size of the value
 * @data: endian format
 *
 * Return: extracted value
 */
unsigned long get_value(unsigned char *header, int offset, int size, int data)
{
	int i;
	unsigned long value;

	value = 0;
	if (data == ELFDATA2MSB)
	{
		for (i = 0; i < size; i++)
			value = (value << 8) + header[offset + i];
	}
	else
	{
		for (i = size - 1; i >= 0; i--)
			value = (value << 8) + header[offset + i];
	}

	return (value);
}

/**
 * print_magic - prints the magic numbers
 * @header: ELF header buffer
 */
void print_magic(unsigned char *header)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", header[i]);
		if (i != EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

/**
 * print_class - prints the ELF class
 * @header: ELF header buffer
 */
void print_class(unsigned char *header)
{
	printf("  Class:                             ");
	switch (header[EI_CLASS])
	{
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", header[EI_CLASS]);
	}
}

/**
 * print_data - prints the data encoding
 * @header: ELF header buffer
 */
void print_data(unsigned char *header)
{
	printf("  Data:                              ");
	switch (header[EI_DATA])
	{
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("<unknown: %x>\n", header[EI_DATA]);
	}
}

/**
 * print_version - prints the ELF version
 * @header: ELF header buffer
 */
void print_version(unsigned char *header)
{
	printf("  Version:                           %d", header[EI_VERSION]);
	if (header[EI_VERSION] == EV_CURRENT)
		printf(" (current)");
	printf("\n");
}

/**
 * print_osabi - prints the OS/ABI
 * @header: ELF header buffer
 */
void print_osabi(unsigned char *header)
{
	printf("  OS/ABI:                            ");
	switch (header[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case 3:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone App\n");
		break;
	default:
		printf("<unknown: %x>\n", header[EI_OSABI]);
	}
}

/**
 * print_abi - prints the ABI version
 * @header: ELF header buffer
 */
void print_abi(unsigned char *header)
{
	printf("  ABI Version:                       %d\n",
		header[EI_ABIVERSION]);
}

/**
 * print_type - prints the ELF type
 * @header: ELF header buffer
 */
void print_type(unsigned char *header)
{
	unsigned long type;

	type = get_value(header, 16, 2, header[EI_DATA]);
	printf("  Type:                              ");
	switch (type)
	{
	case ET_NONE:
		printf("NONE (None)\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("<unknown: %lx>\n", type);
	}
}

/**
 * print_entry - prints the entry point address
 * @header: ELF header buffer
 */
void print_entry(unsigned char *header)
{
	printf("  Entry point address:               ");
	if (header[EI_CLASS] == ELFCLASS32)
		printf("0x%x\n",
			(unsigned int)get_value(header, 24, 4, header[EI_DATA]));
	else
		printf("0x%lx\n", get_value(header, 24, 8, header[EI_DATA]));
}

/**
 * print_header - prints the required ELF header information
 * @header: ELF header buffer
 */
void print_header(unsigned char *header)
{
	printf("ELF Header:\n");
	print_magic(header);
	print_class(header);
	print_data(header);
	print_version(header);
	print_osabi(header);
	print_abi(header);
	print_type(header);
	print_entry(header);
}

/**
 * main - displays the information in the ELF header
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd;
	ssize_t bytes_read;
	unsigned char header[64];

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: elf_header elf_filename\n");
		exit(98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		exit(98);
	}

	bytes_read = read(fd, header, 64);
	if (bytes_read == -1 || bytes_read < 32)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		close_elf(fd);
		exit(98);
	}

	check_elf(header);
	print_header(header);
	close_elf(fd);

	return (0);
}
