// ---------------------------------------------------------
#include "FS.h"

#include "file.h"
#include "koala.h"
#include "vars.h"
#include "utils.h"

const char *filename = "/spiffs/Koala/koala.dat";
File  file;

// ---------------------------------------------------------
// attempt to list all files
void
fileDir (void)
{
    Serial.println (__func__);

    File root = SPIFFS.open ("/");
    File f;

    while ((f = root.openNextFile ()))  {
        Serial.println (f.name ());
    }
}

// ---------------------------------------------------------
// delete selected file
void
fileDelete (void)
{
    Serial.println (__func__);

    File root = SPIFFS.open ("/");
    File f;

    while ((f = root.openNextFile ()))  {
        // display filename
        printf ("  %s:\n", f.name ());

        // wait for keypress
        readLine (s, S_SIZE);
        if ('\n' == s [0])  {
            continue;
        }

        // wait for confirmation
        printf ("   confirm deletion of %s: (D)\n", f.name ());
        readLine (s, S_SIZE);
        if ('D' == s [0])  {
            printf ("    deleting %s\n", f.name());
            SPIFFS.remove (f.name ());
        }
    }

    printf (" %s: done\n", __func__);
}

// ---------------------------------------------------------
void
varsLoad (void)
{
    Serial.println (__func__);

    FILE * fp = fopen (filename, "r");
    if (NULL == fp)  {
        Serial.println ("fopen failed");
        return;
    }

    for (EeVar_t *e = pEeVars; NULL != e->p; e++)  {
         int nread = fread ((void*) e->p, e->nByte, 1, fp);

        if (! nread)  {
            char s [40];
            sprintf (s, " %s: fread incomplete, %d %d",
                        __func__, nread, e->nByte);
            Serial.println (s);
        }
    }

    fclose (fp);
}

// ---------------------------------------------------------
void
varsSave (void)
{
    Serial.println (__func__);

    FILE * fp = fopen (filename, "w");
    if (NULL == fp)  {
        Serial.println ("fopen failed");
        return;
    }

    for (EeVar_t *e = pEeVars; NULL != e->p; e++)  {
         int nread = fwrite ((void*) e->p, e->nByte, 1, fp);

        if (! nread)  {
            char s [40];
            sprintf (s, " %s: fwrite incomplete, %d %d",
                        __func__, nread, e->nByte);
            Serial.println (s);
        }
    }

    fclose (fp);
}
