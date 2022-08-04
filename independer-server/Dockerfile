FROM python:3.9

COPY app/ .
COPY requirements.txt .

RUN pip install -r requirements.txt

CMD ["/bin/bash", "././init-docker.sh"]