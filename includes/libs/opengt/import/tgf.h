#ifndef __OPENGRAPHTHEORY_IMPORT_TGF_H
    #define __OPENGRAPHTHEORY_IMPORT_TGF_H

    #include <iostream>
    #include <sstream>
    #include <map>
    #include <string>
    #include "import.h"

    namespace OpenGraphtheory
    {
        namespace Import
        {

            class ImportFilterTGF : public ImportFilter
            {
                protected:
                    static FactoryRegistrator<ImportFilter> ImportFilterTgfRegistrator;
                public:
                    Graph Import(std::istream& is);
            };

        }
    }

#endif

