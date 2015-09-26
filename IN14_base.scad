outer_dia =  18.67;
lip_height = 2;
lip_width = 1;
total_height = 6.65;

led_length = 6;
led_width = 6;

difference() {

cylinder(r=outer_dia/2, h=total_height, $fn=50);
translate([0, 0, total_height - lip_height]) cylinder(r=(outer_dia/2) - lip_width, h=lip_height + 1, $fn=50);

rotate(360/10,[0,0,1]) translate([-led_length/2,-led_width/2, -1]) cube([led_length, led_width, total_height + 2]);


for (i = [0 : 12]) {

rotate(i * (360/13),[0,0,1]) translate([6,0,-1]) polyhole(total_height + 2, 1.5);
 }
}


module polyhole(h, d) {
    n = max(round(2 * d),3);
    rotate([0,0,180])
        cylinder(h = h, r = (d / 2) / cos (180 / n), $fn = n);
}