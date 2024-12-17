// #include <stdio.h>

// FILE *OpenFile(const char *name, const char *mode)
// {
//     FILE *fp = fopen(name, mode);

//     if (!fp)
//         fprintf(stderr, "Error while opening file \"%s\"\n", name);

//     return fp;
// }

// void Copy(FILE *fpIn, FILE *fpOut)
// {
//     int c;

//     while ((c = getc(fpIn)) != EOF)
//         putc(c, fpOut);
// }

// int main(int argc, char *argv[])
// {
//     FILE *fpIn, *fpOut;

//     switch (argc)
//     {
//     case 2:
//         if (!(fpIn = OpenFile(argv[1], "rb")))
//             return 1;
//         Copy(fpIn, stdout);
//         fclose(fpIn);
//         break;

//     case 3:
//         if (!(fpIn = OpenFile(argv[1], "rb")))
//             return 1;
//         if (!(fpOut = OpenFile(argv[2], "wb")))
//             return 1;
//         Copy(fpIn, fpOut);
//         fclose(fpIn);
//         fclose(fpOut);
//         break;
//     }

//     return 0;
// }


#include <stdio.h>

FILE *OpenFile(const char *name, const char *mode)
{
    FILE *fp = fopen(name, mode);

    if (!fp)
        fprintf(stderr, "Error while opening file \"%s\" with mode \"%s\"\n", name, mode);

    return fp;
}

void CloseFile(FILE *fp, const char *name)
{
    if (fclose(fp) != 0)
        fprintf(stderr, "Error while closing file \"%s\"\n", name);
}

void Copy(FILE *fpIn, FILE *fpOut)
{
    int c;

    while ((c = getc(fpIn)) != EOF)
        putc(c, fpOut);
}

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "Usage: %s input_file [output_file]\n", argv[0]);
        return 1;
    }

    FILE *fpIn, *fpOut;

    switch (argc)
    {
    case 2:
        if (!(fpIn = OpenFile(argv[1], "rb")))
            return 1;
        Copy(fpIn, stdout);
        fclose(fpIn);
        CloseFile(fpIn, argv[1]);
        break;

    case 3:
        if (!(fpIn = OpenFile(argv[1], "rb")))
            return 1;
        if (!(fpOut = OpenFile(argv[2], "wb")))
        {
            fclose(fpIn);
            CloseFile(fpIn, argv[1]);
            return 1;
        }
        Copy(fpIn, fpOut);
        fclose(fpIn);
        CloseFile(fpIn, argv[1]);
        fclose(fpOut);
        CloseFile(fpOut, argv[2]);
        break;
    }

    return 0;
}
