#pragma once

#include<geCore/dtemplates.h>
#include<geGL/ProgramObject.h>
#include<geGL/BufferObject.h>
#include<geGL/VertexArrayObject.h>

namespace ge{
  namespace gl{
    /*
    namespace at{
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ReadFramebuffer     );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(MessageLog          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(PrimitiveMode       );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcY0               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcY1               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Sizes               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(StorageBlockIndex   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(NumAttachments      );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Sources             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Query               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Pointer             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Framebuffer         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ModeAlpha           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Row                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcAlpha            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Zoffset             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcHeight           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Numlevels           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Texture             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Source              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Program             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Location            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Samples             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Sampler             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Usage               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcDepth            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DfactorAlpha        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ModeRGB             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Reset               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(RowBufSize          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(String              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Format              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Framebuffers        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Num_groups_z        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcRGB              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Baseinstance        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ReadOffset          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcWidth            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstZ                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UniformNames        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Name                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstY                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstX                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(H                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Level               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstLevel            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Coords              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Mode                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Timeout             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Basevertex          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Indices             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(X                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Identifier          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(NumViews            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Fixedsamplelocations);
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SfactorAlpha        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UniformBlockIndex   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Attachments         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Sync                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(D                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcName             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Renderbuffers       );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(StorageBlockBinding );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Array               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Buffers             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Index               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ColorNumber         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Bottom              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Pattern             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Dst                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Num_groups_y        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Ret                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Label               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Access              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Props               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Numlayers           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Ref                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SfactorRGB          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Textures            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstTarget           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Offsets             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UniformBlockBinding );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Xfb                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Transpose           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(InfoLog             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Len                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Severities          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Strides             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Instancecount       );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Dpfail              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Offset              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Drawcount           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Xoffset             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Precisiontype       );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Pipeline            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcY                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Lod                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(G                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(BufferMode          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Column              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UniformIndices      );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Samplers            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Ptr                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Shader              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Filter              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Stride              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Length              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Levels              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcTarget           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(W                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Relativeoffset      );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Barriers            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(MaskNumber          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(BufSize             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(First               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Origin              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Clamp               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UniformBlockName    );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Color               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Image               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Height              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(BufferIndex         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Param               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Table               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Message             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Sfail               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Unit                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Size                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UniformIndex        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Stencil             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Span                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Val                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(PropCount           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstX0               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstName             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Textarget           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Pixels              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Width               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Params              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UserParam           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Minlayer            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Type                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Start               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UniformName         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Pipelines           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Indirect            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Src                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DrawFramebuffer     );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Precision           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Drawbuffer          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Yoffset             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(UniformCount        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Pname               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Normalized          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Func                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(MaxCount            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(BinaryFormat        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Buf                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Divisor             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Count               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(B                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Target              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(F                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Arrays              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(WriteTarget         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Enabled             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Value               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(N                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(R                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Values              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(V                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcZ                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcX                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Z                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(WriteBuffer         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(BaseViewIndex       );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Layer               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstAlpha            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Stream              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Dppass              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Varyings            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Condition           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Ids                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DfactorRGB          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstY1               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstY0               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcLevel            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Stages              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Bufsize             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Id                  );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Binary              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Num_groups_x        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(End                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Severity            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Lengths             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Shadertype          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Bufs                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Attribindex         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Range               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Minlevel            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ReadBuffer          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Layered             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Attachment          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Binaryformat        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstRGB              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Shaders             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Map                 );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Renderbuffer        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Buffer              );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcX1               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(SrcX0               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(V0                  );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(V1                  );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(V2                  );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(V3                  );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Internalformat      );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(WriteOffset         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ColumnBufSize       );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Data                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(DstX1               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Types               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Vaobj               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(A                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Origtexture         );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ImageSize           );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Bindingindex        );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Renderbuffertarget  );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Mask                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Face                );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ReadTarget          );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Callback            );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Depth               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Flags               );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(ProgramInterface    );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Y                   );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Strings             );
      DEF_NAMED_TEMPLATE_ATTRIBUTE(Left                );
    }
  */
  }
}

namespace ge{
  namespace core{
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::BufferObject*const&bufferObject){
        return bufferObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::BufferObject>const&sharedBufferObject){
        return sharedBufferObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::ProgramObject*const&programObject){
        return programObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::ProgramObject>const&sharedProgramObject){
        return sharedProgramObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(ge::gl::VertexArrayObject*const&vertexArrayObject){
        return vertexArrayObject->getId();
      }
    template<typename TYPE>
      inline TYPE convertTo(std::shared_ptr<ge::gl::VertexArrayObject>const&sharedVertexArrayObject){
        return sharedVertexArrayObject->getId();
      }

  }
}

