#include <geGL/OcclusionQueriesCommands.h>

namespace ge
{
  namespace gl
  {
    BeginQuery::BeginQuery(GLenum target,GLuint id){
      this->target = target;
      this->id     = id;
    }
    void BeginQuery::apply(){
      glBeginQuery(this->target,this->id);
    }
    EndQuery::EndQuery(GLenum target){
      this->target = target;
    }
    void EndQuery::apply(){
      glEndQuery(this->target);
    }
  }//ogl
}//ge