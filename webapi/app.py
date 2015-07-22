#!flask/bin/python

'''Main Flask App'''

# pylint: disable=import-error
# pylint: disable=invalid-name
# pylint: disable=too-few-public-methods
# pylint: disable=unused-argument

from flask import Flask, jsonify, make_response, request, abort
import ctypes

app = Flask(__name__)

DEFAULT_RETURN_COUNT = 5

class Match(ctypes.Structure):
    '''Python class to mirror match struct in c'''
    _fields_ = [("projection", ctypes.c_char_p),
                ("delta", ctypes.c_double)]

def get_candidates(lng, lat, x, y, count=5):
    '''Main tester function'''
    print "count: ", count
    proj_detective = ctypes.CDLL("projective-detective.so")
    proj_detective.find_projection.restype = ctypes.POINTER(Match)
    proj_detective.find_projection.argtypes = [
        ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_int]

    candidates = proj_detective.find_projection(lng, lat, x, y, count)

    ret_val = {}
    for i in range(count):
        ret_val[candidates[i].projection] = candidates[i].delta

    return ret_val

@app.errorhandler(400)
def bad_request(error):
    '''Return 400 Error'''
    return make_response(jsonify({'error': 'Bad Request'}), 400)

@app.errorhandler(404)
def not_found(error):
    '''Return 404 Error'''
    return make_response(jsonify({'error': 'Not Found'}), 404)

@app.errorhandler(405)
def method_not_allowed(error):
    '''Return 405 Error'''
    return make_response(jsonify({'error': 'Method Not Allowed'}), 405)

@app.route('/')
def index():
    '''Return base'''
    return jsonify({"Message": "Hello, World!"})

@app.route('/find_proj', methods=['GET'])
def find_proj():
    '''Find projection candiates'''
    if not request.args:
        abort(400)
    if not 'x' in request.args:
        abort(400)
    if not 'y' in request.args:
        abort(400)
    if not 'lat' in request.args:
        abort(400)
    if not 'lng' in request.args:
        abort(400)

    x = float(request.args['x'])
    y = float(request.args['y'])
    lng = float(request.args['lng'])
    lat = float(request.args['lat'])

    if 'count' in request.args:
        count = int(request.args['count'])
    else:
        count = DEFAULT_RETURN_COUNT

    return jsonify(get_candidates(lng, lat, x, y, count)), 200
    # return jsonify(get_candidates(-84, 38, 1712479.21678, 182207.371943, count)), 201
    # return jsonify(get_candidates(-84, 38, 5425460, 3892419.8, 5)), 201

if __name__ == '__main__':
    app.run(
        debug=True,
        host='0.0.0.0'
    )

