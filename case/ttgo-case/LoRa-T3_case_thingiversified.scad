// choose part to render
//part                = "case_inlay";
part                = "case_all";
//part                = "case_cover";
//part                = "case_bottom";

T3(part=part,cuts=cuts_t3);

// Fixed values - do not change
dim_t3_board        = [65,27,1.25];
uppers_t3           = 5;
lowers_t3           = 13;
dia_t3_screws       = 2.3;
loc_t3_screws       = [[2.6,1.45],
                       [dim_t3_board[0]-2.6,3.2,0],
                       [dim_t3_board[0]-2.6,dim_t3_board[1]-1.45,0],
                       [2.6,dim_t3_board[1]-3.2,0]];
cuts_t3             = [[[14.8,-8],[7.8,7.8],"front","rnd_indent"],  // antenna port
                       [[2.75,0],[8,3],"left","sqr_indent"], // usb port
                       [[13.4,0],[11.5,3],"left","sqr_indent"],  // sdcard/usb port
                       [[40.8,-dim_t3_board[2]-2.1],[4.65,2.1],"back","sqr_cone"],  // reset
                       [[49.5,-dim_t3_board[2]-4],[9.4,4],"back","sqr_cone"],// switch
                       [[24.6,4.5],[25,17],"top","sqr"]]; //display
space_t3_screws     = 1;


// Example values
// Render options
/*$fn              = 32;
case_part        = "case_all";
render_mode      = "normal";

// Board values
dim_board        = [60,30,2];
space_top        = 7;
space_bottom     = 3;
space_bscrew     = 1;

// Board Screw values
dia_bscrew       = 3.2;
loc_bscrews      = [[3.5,3.5],
                    [dim_board[0]-3.5,3.5],
                    [dim_board[0]-3.5,dim_board[1]-3.5],
                    [3.5,dim_board[1]-3.5]];                    

// Case Screw values
dia_cscrew       = 3;
dia_chead        = 5.5;
height_chead     = 2.5;
                    
// Case values
wall_frame       = 1.2;
rim              = 1;
mki              = 2;
                  
// Port values and locations
port_extend      = 20;
cuts             = [[[0,0],[5,3],"front","sqr_indent"],       
                    [[0,0],[5,3],"back","sqr_indent"],
                    [[0,0],[5,3],"left","sqr"],
                    [[0,0],[5,3],"right","sqr"],
                    [[0,0],[5,3],"top","sqr"],
                    [[0,0],[5,3],"bottom","sqr_indent"],
                    ];

case(part=case_part,
     render_mode=render_mode,
     
     wall_frame=wall_frame,
     rim=rim,
     mki=mki,
     port_length=wall_frame+rim,
     port_extend=port_extend,
          
     dim_board=dim_board,
     cuts=cuts,
     space_top=space_top,
     space_bottom=space_bottom,
     space_bscrew=space_bscrew,

     dia_cscrew=dia_cscrew,
     dia_chead=dia_chead,
     height_chead=height_chead,
     
     dia_bscrew=dia_bscrew,
     loc_bscrews=loc_bscrews);*/

//module to create openings for a electronics board
// d        - cube dimension [x,y,z] 
// cuts     - array of cuts to be created
// extend   - amount to extend outwards
// move     - move inwards(-)/outwards(+)
//
// cuts: 
//          [[[x,y],    // location
//            [x,y],    // size
//            side,     // side
//            shape],   // shape
//           [...],...]
//      
//      location:
//          x/y coordinates of lower left of opening,
//          meassured from the boards left top
//      size:
//          x/y dimension of the opening
//      side:
//          Side of the board, one of
//          front,back,left,right,top,bottom
//      shape:
//          shape of the opening, one of
//           square/rnd,
//           sqr_cone/rnd_cone,
//           sqr_indent/rnd_indent,
//           sqr_button/rnd_button

// Example
//    $fn=32;
//    board_dim=[20,20,1.5];
//    length=5;
//    extend=7;
//    move=0;
//    grow=4;
//    cut_location=[0,0];
//    cut_size=[3,2];
//    cuts=[[cut_location,cut_size,"front","sqr"],
//          [cut_location,cut_size,"back","sqr_cone"],
//          [cut_location,cut_size,"left","sqr_indent"],
//          [cut_location,cut_size,"right","sqr_button"],
//          [cut_location,cut_size,"top","rnd_indent"],
//          [cut_location,cut_size,"bottom","rnd_button"]];
//          
//    %cube(board_dim);
//    make_cuts_v2(dim=board_dim,
//                 cuts=cuts,
//                 length=length,
//                 extend=extend,
//                 move=move,
//                 grow=grow);

module make_cuts_v2(dim=[10,10,0],
                    cuts=[[[0,0],[10,10,10],"front","sqr"]],
                    length=1,
                    extend=0,
                    move=0,
                    grow=2){
                     
    for(cut=cuts){
        loc_x   = cut[0][0];
        loc_y   = cut[0][1];
        x       = cut[1][0];
        y       = cut[1][1];
        side    = cut[2];
        shape   = cut[3];
        

        if(side=="front" || side=="back" || side==0 || side==1) {
            translate([x/2,0,y/2]+[0,0,dim[2]]){        // move x,y to 0 and on top of board
                if(side=="front" || side==0)
                    translate([loc_x,0,loc_y])          // move to location
                        rotate([90,0,0])                // rotate up
                            translate([0,0,+length/2])       // move up to z=0
                                mkshape(x,y,length,shape,extend,move,grow);   // create centered shape

                if(side=="back" || side==1)
                    translate([dim[0]-x,0,0]+[-loc_x,0,loc_y])
                        rotate([270,0,0])
                            translate([0,0,+length/2+dim[1]])
                                mkshape(x,y,length,shape,extend,move,grow);
            }
        }

        if(side=="right" || side=="left" || side==2 || side==3 ) {
            translate([0,x/2,y/2]+[0,0,dim[2]]) {
                if(side=="right" || side==3)
                    translate([0,loc_x,loc_y]+[0,0,0])
                        rotate([90,0,90])
                            translate([0,0,+length/2+dim[0]])
                                mkshape(x,y,length,shape,extend,move,grow);
            
                if(side=="left" || side==2)
                    translate([0,dim[1]-x,0]+[0,-loc_x,loc_y])
                        rotate([90,0,270])
                            translate([0,0,+length/2])
                                mkshape(x,y,length,shape,extend,move,grow);
            }
        }

        if(side=="top" || side=="bottom" || side==4 || side==5 ) {
            translate([x/2,y/2,0]) {          
                if(side=="top" || side==4)
                    translate([loc_x,loc_y,0])
                        rotate([0,0,0])
                            translate([0,0,+length/2+dim[2]])
                                mkshape(x,y,length,shape,extend,move,grow);
                
                if(side=="bottom" || side==5)
                    translate([0,dim[1]-y,0]+[loc_x,-loc_y,0])
                        rotate([180,0,0])
                            translate([0,0,+length/2]) 
                                mkshape(x,y,length,shape,extend,move,grow);
            }
        }
    }
}

// Create shapes that will be cut out
module mkshape(x,y,l,shape,extend,move,grow=4){
    // square shapes
    if(shape=="sqr"){
        translate([0,0,extend/2+move]){
            cube([x,y,l+extend],center=true);
        }
    }
    if(shape=="sqr_cone"){
        translate([0,0,move]){
            hull(){
                cube([x,y,l],center=true);
                translate([0,0,l/2-0.000001/2]){
                    cube([x+grow,y+grow,0.000001],center=true);
                }
                if(extend>=0){
                    translate([0,0,l/2+extend-0.000001/2]){
                        cube([x+grow,y+grow,0.000001],center=true);
                    }
                }
            }
        }
    }
    if(shape=="sqr_indent"){
        translate([0,0,move]){
            cube([x,y,l],center=true);
            translate([0,0,+l/4+extend/2]){
                cube([x+grow,y+grow,l/2+extend],center=true);
            }
        }
    }
    if(shape=="sqr_button"){
        translate([0,0,move]){
            cube([x,y,l],center=true);
            translate([0,0,-l/4]){
                cube([x+grow,y+grow,l/2],center=true);
            }
            translate([0,0,l/2+extend/2]){
                cube([x+grow,y+grow,extend],center=true);
            }
        }
    }
    
    // round shapes
    if(shape=="rnd"){
        translate([-x/2,-y/2,extend/2+move]){
            resize([0,y,0]){
                cylinder(d=x,h=l+extend,center=true);
            }
        }
    }
    if(shape=="rnd_cone"){
        translate([-x/2,-y/2,+move]){
            resize([0,y+grow,0]){
                cylinder(d1=x,d2=x+grow,h=l,center=true);
            }
            translate([0,0,l/2+extend/2]){
                resize([0,y+grow,0]){
                    cylinder(d=x+grow,h=extend,center=true);
                }
            }
        }        
    }
    if(shape=="rnd_indent"){
            translate([-x/2,-y/2,-l/4+move]){
                resize([0,y,0]){
                    cylinder(d=x,h=l/2,center=true);
                }
            }
            translate([-x/2,-y/2,l/4+move]){
                resize([0,y+grow,0]){
                    cylinder(d=x+grow,h=l/2,center=true);
                }
            }
            translate([-x/2,-y/2,l/2+extend/2+move]){
                resize([0,y+grow,0]){
                    cylinder(d=x+grow,h=extend,center=true);
                }
            }
    }
    if(shape=="rnd_button"){
            translate([-x/2,-y/2,l/4+move]){
                resize([0,y,0]){
                    cylinder(d=x,h=l/2,center=true);
                }
            }
            translate([-x/2,-y/2,-l/4+move]){
                resize([0,y+grow,0]){
                    cylinder(d=x+grow,h=l/2,center=true);
                }
            }
            translate([-x/2,-y/2,l/2+extend/2+move]){
                resize([0,y+grow,0]){
                    cylinder(d=x+grow,h=extend,center=true);
                }
            }
    }
}
// Module for painting cube with rounded corners in xy directions

module cube_round_xy(dim,mki){
    if(mki<=0){
        cube(dim);
    }
    else {
        translate([mki/2,mki/2,0]){
            linear_extrude(dim[2]){
                minkowski(){
                    square([dim[0]-mki,dim[1]-mki]);
                    circle(d=mki);
                }
            }
        }
    }
}
// Module for creating screw holes based on an array of [x,y,z] locations



module screw_holes(loc,dia,h,fn=32){
    for(l=loc){
        translate(l){
            cylinder(d=dia,h=h,$fn=fn);
        }
    }
}

module corner_latches(dim_b,loc_s,dia_s,space_s,height_s){
    //calculate corner points
    loc_c   = [[[0,0],[loc_s[0][0],0],[loc_s[0][0],loc_s[0][1]],[0,loc_s[0][1]]],
               [[loc_s[1][0],0],[dim_b[0],0],[dim_b[0],loc_s[1][1]],[loc_s[1][0],loc_s[1][1]]],
               [[loc_s[2][0],loc_s[2][1]],[dim_b[0],loc_s[2][1]],[dim_b[0],dim_b[1]],[loc_s[2][0],dim_b[1]]],
               [[0,loc_s[3][1]],[loc_s[3][0],loc_s[3][1]],[loc_s[3][0],dim_b[1]],[0,dim_b[1]]]]; // corners
    
    difference(){
        for(i=[0 : len(loc_c)-1]){
            hull(){
                linear_extrude(height_s)
                    polygon(points=loc_c[i]);
                translate(loc_s[i]){
                    cylinder(d=dia_s+space_s,h=height_s);
                }
            }
        }
    }
}



     
function calc_height_case(height_frame,
                          height_top,
                          height_floor) = height_frame+height_top+height_floor;
                          
function calc_height_bscrew(space_bottom,
                            height_bhead) = space_bottom-height_bhead;
                            
function calc_height_frame(space_top,
                           space_bottom,
                           dim_board) = space_top+space_bottom+dim_board[2];
                           
function calc_height_floor(height_chead,wall_frame) = max(height_chead+wall_frame,wall_frame);
function calc_height_cover(height_case,height_bottom) = height_case-height_bottom;
function calc_dim_case(dim_frame,
                       wall_case,
                       height_case) = [dim_frame[0]+2*wall_case,
                                       dim_frame[1]+2*wall_case,
                                       height_case];
function calc_wall_case(dia_chead,wall_frame) = max(dia_chead-wall_frame,wall_frame);
function calc_dim_frame(dim_board,
                        wall_frame,
                        rim,
                        height_frame) = [dim_board[0]+2*(wall_frame+rim),
                                         dim_board[1]+2*(wall_frame+rim),
                                         height_frame];
     
// case module
module case(part="frame", // which part to render
            render_mode="normal", // how to render
            
            wall_frame=1.4,         // wall_frame thickness
            rim=0.3,         // rim between board and wall_frame thickness
            mki=2,       // corner rounding value (0=no rounding)
            gap=0.3,
            grow=2,
            port_length,
            port_extend=10,
            
            dim_board,     // board dimension (without components)
            cuts,      // location of port openings ()
            space_top,        // height of components on top of board
            space_bottom,        // height of components below board
            space_bscrew=1,   // space around board screw holes
            
            dia_cscrew = 3.3, // case screw values
            dia_chead = 5.5,
            height_chead = 3,
            height_bottom = 10, // height of bottom case part
            
            text = "TSM",
            font = "Liberation Sans:style=Bold",
            loc_text = [10,10],
            size_text = 20,
     
            dia_bscrew=3,       // screw diameter
            height_bhead=2.4,
            render_floor=1,
            render_top=1,
            loc_bscrews)        // screw locations (array of [x,y] pairs, 
                                //starting left lower corner, counterclockwise)  
{
    // calculate values;
    height_bscrew   = calc_height_bscrew(space_bottom,height_bhead);
    
    height_inlay    = space_bottom;
    height_headspace = space_top;
    height_floor    = calc_height_floor(height_chead,wall_frame);
    height_top      = height_floor;
    
    height_frame    = calc_height_frame(space_top,space_bottom,dim_board);
    dim_frame       = calc_dim_frame(dim_board,wall_frame,rim,height_frame);
    
    wall_case       = calc_wall_case(dia_chead,wall_frame);
    height_case     = calc_height_case(height_frame,height_top,height_floor);
    dim_case        = calc_dim_case(dim_frame,wall_case,height_case);
    
    height_cover    = calc_height_cover(height_case,height_bottom);    

    loc_cscrews     = [[dia_chead/2,dia_chead/2-0.36844],
                       [dim_case[0]-dia_chead/2,dia_chead/2-0.36844],
                       [dim_case[0]-dia_chead/2,dim_case[1]-dia_chead/2+0.36844],
                       [dia_chead/2,dim_case[1]-dia_chead/2+0.36844]];
    loc_corner_cuts = [[0,0],
                       [dim_case[0],0],
                       [dim_case[0],dim_case[1]],
                       [0,dim_case[1]]];
    
    /////////////////////////////////////////////////////////////
    // Render the requested part
    /////////////////////////////////////////////////////////////
    
    if(part=="frame"){
        frame();
        //#cube_round_xy(dim_frame,mki);
    }
    
    if(part=="case_inlay"){
        case_inlay();
    }
    
    if(part=="case_bottom"){
        case_bottom();
    }
    
    if(part=="case_cover"){
        case_cover();
    }
    
    if(part=="case_all"){
        case_bottom();
        case_cover();
        //case_inlay();
    }
    
    if(part=="case_shape"){
        cube_round_xy([dim_case[0],dim_case[1],height_case],mki);
    }
    
    if(part=="cutout_shape"){
        cutouts_case();
    }
    
    /////////////////////////////////////////////////////////////
    // Part modules
    /////////////////////////////////////////////////////////////
    
    module case_inlay(){
        translate([wall_case,wall_case,height_floor]){
            difference(){
                frame();
                translate([0,0,space_bottom]){
                    cube_round_xy(dim_frame,mki);
                }
            }
        }
    }
    
    module case_bottom(){
        module _bottom(){
            difference(){
                bottom();
                cutouts_case();
                cutout_case_screws();
            }
        }
        
        if(render_floor==0){
            difference(){
                _bottom();
                part_floor_frame();
            }
        }
        else {
            _bottom();
        }
    }
    
    module case_cover(){
        module _cover(){
            difference(){
                union(){
                    difference(){
                        cover();
                        cutouts_case();
                    }
                    difference(){
                        translate([wall_case,wall_case,height_floor]){
                            frame();
                        }
                        case_inlay();
                    }
                }
                cutout_case_screws();
                cutout_font();
            }
        }
         
        if(render_top==0){
            difference(){
                _cover();
                part_top_frame();
            }
        }
        else {   
            _cover();
        }
    }
    
    module bottom(){
        // bottom case shape
        cube_round_xy([dim_case[0],dim_case[1],height_bottom],mki);
    }
    
    module cover(){
        translate([0,0,height_bottom]){
            cube_round_xy([dim_case[0],dim_case[1],height_cover],mki);
        }
    }
    
    module part_top_frame(){
        translate([wall_case+rim+wall_frame,wall_case+rim+wall_frame,height_case-height_top]){
            cube_round_xy([dim_board[0],dim_board[1],height_top],mki);
        }
    }
        
    module part_floor_frame(){
        translate([wall_case+rim+wall_frame,wall_case+rim+wall_frame,0]){
            cube_round_xy([dim_board[0],dim_board[1],height_floor],mki);
        }
    }
    
    module frame(){
        difference(){
            union(){
                outer_frame();
                inner_frame();
            }
            cutout_ports();
        }
    }
    
    
    /////////////////////////////////////////////////////////////
    // part composition
    /////////////////////////////////////////////////////////////
    
    module inner_frame(){
        rim();
        board_screws();
    }
       
    module outer_frame(){
        difference(){
            cube_round_xy(dim_frame,mki);
            cutout_board();
        }
    }
    
    module rim(){
        translate([0,0,space_bottom-height_bscrew]){
            difference(){
                    translate([wall_frame,wall_frame,0]){
                        cube([dim_board[0]+2*rim,dim_board[1]+2*rim,height_bscrew]);
                    }
                    translate([wall_frame+rim,wall_frame+rim,0]){
                       cube([dim_board[0],dim_board[1],height_bscrew]);
                }
            }
        }
    }
            
    module board_screws(){
        translate([0,0,space_bottom-height_bscrew]){
            translate([wall_frame+rim,wall_frame+rim,0]){
                difference(){
                    corner_latches(dim_board,loc_bscrews,dia_bscrew,space_bscrew,height_bscrew);
                    screw_holes(loc=loc_bscrews,dia=dia_bscrew,h=height_frame);
                }
            }
        }
    }
    
    
    /////////////////////////////////////////////////////////////
    // Cutout modules
    /////////////////////////////////////////////////////////////
    
    module cutouts_case(){
        translate([wall_case,wall_case,height_floor]){
            cutout_frame_bottom();
            cutout_frame_cover();
            cutout_ports();
        }
    }
    
    // Create cutout in case for adding bottom frame part
    //cutout_frame_bottom();
    module cutout_frame_bottom(){
        // cut out for inlay
        translate([-gap,-gap,-gap]){
            cube_round_xy([dim_frame[0]+2*gap,
                           dim_frame[1]+2*gap,
                           height_inlay+2*gap],mki);
        }
    }
    
    // Create cutout in case for adding cover frame part
    //cutout_frame_cover();
    module cutout_frame_cover(){
        // cut out for inlay
        translate([0,0,height_inlay]){
            cube_round_xy([dim_frame[0],
                           dim_frame[1],
                           dim_board[2]+space_top],mki);
        }
    }
        
    // Cutout for board in frame
    //cutout_board();
    module cutout_board(){
        translate([wall_frame,wall_frame,0]){
            cube([dim_board[0]+2*rim,dim_board[1]+2*rim,dim_frame[2]]);
        }
    }
    
    // Create cutout font on cover
    module cutout_font(){
        translate([loc_text[0],loc_text[1],height_case-wall_case/2]){
            linear_extrude(wall_case/2){
                text(text=text,font=font,size=size_text,valign="bottom",halign="left");
            }
        }
    }
    
    // Create cutout for case screws
    //cutout_case_screws();
    module cutout_case_screws(){
        // cut out screw holes
        screw_holes(loc=loc_cscrews,dia=dia_cscrew,h=height_case);
        // cut out screw heads bottom
        screw_holes(loc=loc_cscrews,dia=dia_chead,h=height_chead,fn=6);
        // cut of corners
        screw_holes(loc=loc_corner_cuts,dia=dia_chead,h=height_chead);
        // cut out screw heads top
        translate([0,0,height_case-height_chead]){
            screw_holes(loc=loc_cscrews,dia=dia_chead,h=height_chead);
            screw_holes(loc=loc_corner_cuts,dia=dia_chead,h=height_chead);
        }
    }

    module cutout_ports(){
        translate([wall_frame+rim,wall_frame+rim,space_bottom]){
            make_cuts_v2(dim=dim_board,
                         cuts=cuts,
                         //length=port_length,
                         length=4*wall_frame+4*rim,
                         //extend=height_cover,
                         extend=port_extend,
                         move=-rim-wall_frame-wall_frame/2,
                         grow=grow);
        }
    }
}


module T3(part                = "all_case",
          dia_cscrew          = 2.3,
          dia_chead           = 4.7,
          height_chead        = 1.8,
          text                = "TSM",
          font                = "Source Sans Pro:style=Bold",
          size_text           = 8,
          loc_text            = [4.5,14.5],
          wall                = 1.2,
          rim                 = 0.8,
          port_length         = 30,
          mki                 = 4,
          grow                = 4,
          height_bottom       = 11,
          render_floor        = 1,
          render_top          = 1,
          cuts){



    case(part=part,
         dim_board=dim_t3_board,
         space_top=uppers_t3,
         space_bottom=lowers_t3,
         dia_bscrew=dia_t3_screws,
         space_bscrew=space_t3_screws,     
         loc_bscrews=loc_t3_screws,
         cuts=cuts,
         wall_frame=wall,
         rim=rim,
         grow=grow,
         dia_cscrew=dia_cscrew,
         dia_chead=dia_chead,
         height_chead=height_chead,
         height_bottom=height_bottom,
         mki=mki,
         text=text,
         size_text=size_text,
         loc_text=loc_text,
         font=font,
         port_length=port_length,
         render_floor=render_floor,
         render_top=render_top);
}