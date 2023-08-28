var request = require('request'),
    expect = require('chai').expect,
    baseUrl = 'http://localhost:3000';

describe('Graphs', function() {
  it('should list ALL graphs on GET /api/graphs', function (done) {
    request(baseUrl + '/api/graphs', function (error, response, body) {
      expect(response.statusCode).to.equal(200);
      done();
    });
  });

  it('should add a NEW graph on POST /api/graphs', function (done) {
    request.post(
      {
        url: baseUrl + '/api/graphs',
        form: {
          title: 'Hello World'
        }
      },
      function(error, response, body) {
        expect(response.statusCode).to.equal(200);
        done();
      }
    );
  });

  it('should list a SINGLE graph on GET /api/graph/:id', function (done) {
    request(baseUrl + '/api/graphs', function (error, response, body) {
      var allGraphs = JSON.parse(body).graphs;
      var singleGraph = allGraphs[allGraphs.length - 1];
      request(baseUrl + '/api/graphs/' + singleGraph._id, function (error, response, body) {
        expect(response.statusCode).to.equal(200);
        done();
      });
    });
  });

  it('should update a SINGLE graph on PUT /api/graphs/:id', function (done) {
    request(baseUrl + '/api/graphs', function (error, response, body) {
      var allGraphs = JSON.parse(body).graphs;
      var singleGraph = allGraphs[allGraphs.length - 1];
      request.put(
        {
          url: baseUrl + '/api/graphs/' + singleGraph._id,
          form: {
            title: 'Goodbye'
          }
        },
        function (error, response, body) {
          expect(response.statusCode).to.equal(200);
          done();
        }
      );
    });
  });

  it('should delete a SINGLE graph on DELETE /graphs/:id', function (done) {
    request(baseUrl + '/api/graphs', function (error, response, body) {
      var allGraphs = JSON.parse(body).graphs;
      var singleGraph = allGraphs[allGraphs.length - 1];
      request.del(baseUrl + '/api/graphs/' + singleGraph._id, function (error, response, body) {
        expect(response.statusCode).to.equal(200);
        done();
      });
    });
  });
});
