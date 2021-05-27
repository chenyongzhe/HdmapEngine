from matplotlib.patches import Polygon






def _draw_polygon(polygon, ax, color_val):
    # todo(zero): need to fix
    pxy = []
    for point in polygon.point:
      pxy.append([point.x, point.y])
    polygon = Polygon(pxy, True)
    ax.add_patch(polygon)
