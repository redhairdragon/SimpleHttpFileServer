from locust import HttpUser, task


class FileDownloadingUser(HttpUser):
    @task(100)
    def smallFile(self):
        r = self.client.get("/small")
        if r.content != self.small:
            r.failure("Got wrong response")

    @task(1)
    def largeFile(self):
        r = self.client.get("/large")
        if r.content != self.large:
            r.failure("Got wrong response")

    def on_start(self):
        with open('large', 'rb') as file:
            self.large = file.read()
        with open('small', 'rb') as file:
            self.small = file.read()
