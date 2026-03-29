#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * get_value - gets a value from the ELF header
 * @header: buffer containing the ELF header
 * @offset: starting position of the value
 * @size: size of the value in bytes
 * @data: endianness format
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
 * print_magic - prints the magic bytes
 * @header: buffer containing the ELF header
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
 * print_osabi - prints the OS/ABI field
 * @header: buffer containing the ELF header
 */
void print_osabi(unsigned char *header)
{
	printf("  OS/ABI:                            ");
	switch (header[EI_OSABI])
	{
	case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
	case ELFOSABI_HPUX: printf("UNIX - HP-UX\n"); break;
	case ELFOSABI_NETBSD: printf("UNIX - NetBSD\n"); break;
	case ELFOSABI_LINUX: printf("UNIX - Linux\n"); break;
	case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
	case ELFOSABI_IRIX: printf("UNIX - IRIX\n"); break;
	case ELFOSABI_FREEBSD: printf("UNIX - FreeBSD\n"); break;
	case ELFOSABI_TRU64: printf("UNIX - TRU64\n"); break;
	case ELFOSABI_ARM: printf("ARM\n"); break;
	case ELFOSABI_STANDALONE: printf("Standalone App\n"); break;
	default: printf("<unknown: %x>\n", header[EI_OSABI]); break;
	}
}

/**
 * print_type - prints the file type
 * @header: buffer containing the ELF header
 */
void print_type(unsigned char *header)
{
	unsigned long type;

	type = get_value(header, 16, 2, header[EI_DATA]);
	printf("  Type:                              ");
	switch (type)
	{
	case ET_NONE: printf("NONE (None)\n"); break;
	case ET_REL: printf("REL (Relocatable file)\n"); break;
	case ET_EXEC: printf("EXEC (Executable file)\n"); break;
	case ET_DYN: printf("DYN (Shared object file)\n"); break;
	case ET_CORE: printf("CORE (Core file)\n"); break;
	default: printf("<unknown: %lx>\n", type); break;
	}
}

/**
 * print_header - prints the required ELF header information
 * @header: buffer containing the ELF header
 */
void print_header(unsigned char *header)
{
	printf("ELF Header:\n");
	print_magic(header);
	printf("  Class:                             ");
	if (header[EI_CLASS] == ELFCLASS32)
		printf("ELF32\n");
	else if (header[EI_CLASS] == ELFCLASS64)
		printf("ELF64\n");
	else
		printf("<unknown: %x>\n", header[EI_CLASS]);
	printf("  Data:                              ");
	if (header[EI_DATA] == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (header[EI_DATA] == ELFDATA2MSB)
		printf("2's complement, big endian\n");
	else
		printf("<unknown: %x>\n", header[EI_DATA]);
	printf("  Version:                           %d", header[EI_VERSION]);
	if (header[EI_VERSION] == EV_CURRENT)
		printf(" (current)");
	printf("\n");
	print_osabi(header);
	printf("  ABI Version:                       %d\n", header[EI_ABIVERSION]);
	print_type(header);
	if (header[EI_CLASS] == ELFCLASS32)
		printf("  Entry point address:               0x%x\n",
			(unsigned int)get_value(header, 24, 4, header[EI_DATA]));
	else
		printf("  Entry point address:               0x%lx\n",
			get_value(header, 24, 8, header[EI_DATA]));
}

/**
 * main - displays the information contained in the ELF header
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd, close_check;
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
		close(fd);
		exit(98);
	}
	if (header[0] != 0x7f || header[1] != 'E' ||
		header[2] != 'L' || header[3] != 'F')
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
		close(fd);
		exit(98);
	}
	print_header(header);
	close_check = close(fd);
	if (close_check == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(98);
	}
	return (0);
}
