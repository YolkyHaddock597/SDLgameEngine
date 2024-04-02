struct sprite;
struct circle;
struct rectangle;

/* the renderer struct is hidden in the implementation; */
typedef struct renderer renderer;

renderer *renderer_create(void);
void renderer_destroy(renderer *r);

void render_sprite(renderer *r, struct sprite *sprite);
void render_circle(renderer *r, struct circle *circle);
void render_rectangle(renderer *r, struct rectangle *rectangle);
