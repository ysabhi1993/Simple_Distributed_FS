#ifndef _DIRENTRY_H_
#define _DIRENTRY_H_

#include "freeNode.hpp"
#include "inode.hpp"

#include <list>
#include <memory>
#include <string>
#include <sys/types.h>

enum EntryType {file, dir};

class DirEntry : public std::enable_shared_from_this<DirEntry>{
      DirEntry();
    public:
      static std::shared_ptr<DirEntry> make_dir (const std::string name, 
                                                 const std::shared_ptr<DirEntry> parent);
      static std::shared_ptr<DirEntry> make_file(const std::string name,
                                                 const std::shared_ptr<DirEntry> parent,
                                                 const std::shared_ptr<Inode> &inode = nullptr);
      uint block_size;
      EntryType type;
      std::string name;
      std::weak_ptr<DirEntry> parent;
      std::weak_ptr<DirEntry> self;
      std::shared_ptr<Inode> inode;
      std::list<std::shared_ptr<DirEntry> > contents;
      bool is_locked;

      std::shared_ptr<DirEntry> find_child(const std::string name) const;
      std::shared_ptr<DirEntry> add_dir(const std::string name);
      std::shared_ptd<DirEntry> add_file(const std::string name);
};

#endif 